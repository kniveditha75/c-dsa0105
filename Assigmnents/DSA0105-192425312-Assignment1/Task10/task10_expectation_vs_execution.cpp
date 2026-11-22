#include <iostream>
#include <iomanip>
#include <climits>

// Task 10: Compare Expectations with Execution (20k, 500k, 3M journeys; int vs long long vs double)

int main() {
    std::cout << "=== TASK 10: SCALING & PRECISION COMPARISON ===\n\n";

    // Mix of fares with non-exact binary representation in rupees (e.g., Rs 13.33 = 1333 paise)
    // Repeating cycle of 3 trips: Rs 10.00 (1000p), Rs 23.33 (2333p), Rs 36.00 (3600p)
    const long long cyclePaise[3] = {1000, 2333, 3600};
    const double cycleRupees[3] = {10.00, 23.33, 36.00};

    long long scales[3] = {20000LL, 500000LL, 3000000LL};
    const char* labels[3] = {"1 Station (20,000)", "1 Line (500,000)", "Whole Network (3,000,000)"};

    std::cout << std::left << std::setw(28) << "Scale"
              << std::setw(18) << "Exact (Rs)"
              << std::setw(18) << "Double (Rs)"
              << std::setw(16) << "Drift (Rs)"
              << "32-bit int Status\n";
    std::cout << std::string(95, '-') << "\n";

    for (int s = 0; s < 3; ++s) {
        long long n = scales[s];
        long long exactPaise = 0;
        double doubleRupees = 0.0;
        int intPaise = 0; // Deliberately testing 32-bit signed overflow

        for (long long i = 0; i < n; ++i) {
            int idx = static_cast<int>(i % 3);
            exactPaise += cyclePaise[idx];
            doubleRupees += cycleRupees[idx];
            intPaise += static_cast<int>(cyclePaise[idx]); // UB if overflows; observed on 2's complement
        }

        double exactRs = static_cast<double>(exactPaise) / 100.0;
        double drift = doubleRupees - exactRs;

        std::cout << std::left << std::setw(28) << labels[s]
                  << std::fixed << std::setprecision(2)
                  << std::setw(18) << exactRs
                  << std::setw(18) << doubleRupees
                  << std::setprecision(6) << std::setw(16) << drift
                  << (exactPaise > INT_MAX ? "OVERFLOW (" + std::to_string(intPaise) + ")" : "OK")
                  << "\n";
    }
    return 0;
}
