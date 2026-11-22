#include <iostream>
#include <chrono>
#include <vector>
#include <memory>

// Task B3: Cost Comparison — Virtual Functions vs Switch vs Exceptions

enum BillType { OP, IP, DAYCARE };

struct SimpleBill {
    BillType type;
    double param1, param2;
    double compute() const {
        switch (type) {
            case OP: return param1 + param2;
            case IP: return param1 * param2 + 1000;
            case DAYCARE: return param1 * 1.5;
        }
        return 0;
    }
};

class PolyBill {
public:
    virtual ~PolyBill() = default;
    virtual double total() const = 0;
};

class PolyOP : public PolyBill {
    double c, t;
public:
    PolyOP(double cc, double tt) : c(cc), t(tt) {}
    double total() const override { return c + t; }
};

int main() {
    std::cout << "=== TASK B3: PERFORMANCE BENCHMARKING ===\n";
    const int N = 1000000;

    // Switch benchmark
    std::vector<SimpleBill> sbills(N, {OP, 500.0, 1200.0});
    auto start = std::chrono::high_resolution_clock::now();
    double sum1 = 0;
    for (int i = 0; i < N; ++i) sum1 += sbills[i].compute();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Switch sum: " << sum1 << " | Time: " 
              << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    // Polymorphic benchmark
    std::vector<std::unique_ptr<PolyBill>> pbills;
    pbills.reserve(N);
    for (int i = 0; i < N; ++i) pbills.push_back(std::make_unique<PolyOP>(500.0, 1200.0));
    start = std::chrono::high_resolution_clock::now();
    double sum2 = 0;
    for (int i = 0; i < N; ++i) sum2 += pbills[i]->total();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Polymorphic sum: " << sum2 << " | Time: " 
              << std::chrono::duration<double, std::milli>(end - start).count() << " ms\n";

    return 0;
}
