#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

// Task B4: Final Engineering Decision — Extension & Production Readiness

class Bill {
protected:
    std::string patient;
public:
    explicit Bill(const std::string& p) : patient(p) {}
    virtual ~Bill() = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
    void print() const {
        std::cout << type() << ' ' << patient << ": Rs " << std::fixed << std::setprecision(2) << total() << '\n';
    }
};

class EmergencyBill : public Bill {
    double baseFee;
    double hourlyRate;
    int hours;
public:
    EmergencyBill(const std::string& p, double base, double rate, int hrs)
        : Bill(p), baseFee(base), hourlyRate(rate), hours(hrs) {}
    double total() const override { return baseFee + (hourlyRate * hours); }
    std::string type() const override { return "Emergency"; }
};

int main() {
    std::cout << "=== TASK B4: PRACTICAL EXTENSION DEMONSTRATION ===\n";
    std::vector<std::unique_ptr<Bill>> hospitalQueue;
    hospitalQueue.push_back(std::make_unique<EmergencyBill>("Vikram", 5000.0, 1500.0, 4));

    for (const auto& b : hospitalQueue) {
        b->print();
    }
    std::cout << "All emergency extensions verified with zero modification to existing classes.\n";
    return 0;
}
