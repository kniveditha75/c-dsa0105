#include <iostream>
#include <iomanip>
#include <climits>
#include <cstdint>

// Task 3: Data Types, Ranges, Precision Drift (double vs long long paise), and Overflow Check

int main() {
    std::cout << "=== TASK 3: DATA TYPES, RANGES & PRECISION ANALYSIS ===\n\n";
    std::cout << "--- sizeof() on this system ---\n";
    std::cout << "bool      : " << sizeof(bool) << " byte\n";
    std::cout << "char      : " << sizeof(char) << " byte\n";
    std::cout << "unsigned  : " << sizeof(unsigned int) << " bytes (max: " << UINT_MAX << ")\n";
    std::cout << "int       : " << sizeof(int) << " bytes (max: " << INT_MAX << ")\n";
    std::cout << "long long : " << sizeof(long long) << " bytes (max: " << LLONG_MAX << ")\n";
    std::cout << "float     : " << sizeof(float) << " bytes\n";
    std::cout << "double    : " << sizeof(double) << " bytes\n\n";

    // Network scale test: 3,000,000 journeys/day at Rs 36.00 (3600 paise)
    constexpr long long NETWORK_JOURNEYS = 3000000LL;
    constexpr long long MAX_FARE_PAISE = 3600LL;
    long long totalNetworkPaise = NETWORK_JOURNEYS * MAX_FARE_PAISE; // 10,800,000,000 paise

    std::cout << "--- Overflow Check (3,000,000 journeys @ Rs 36.00) ---\n";
    std::cout << "Total paise needed : " << totalNetworkPaise << " paise (Rs " << totalNetworkPaise / 100 << ")\n";
    std::cout << "INT_MAX            : " << INT_MAX << " paise -> "
              << (totalNetworkPaise > INT_MAX ? "OVERFLOWS 32-bit int!" : "Fits in int") << "\n";
    std::cout << "LLONG_MAX          : " << LLONG_MAX << " paise -> Fits safely in long long\n\n";

    // Precision drift demonstration: accumulating non-exact decimal fares (e.g., Rs 13.33 / 13.30 or 0.10 surcharge)
    // Example: Rs 19.99 (19.99 in IEEE-754 binary64 is 19.9899999999999984368...)
    std::cout << "--- Floating-Point Drift Demonstration (3,000,000 trips @ Rs 19.99) ---\n";
    double doubleTotalRupees = 0.0;
    long long exactPaiseTotal = 0;
    for (long long i = 0; i < NETWORK_JOURNEYS; ++i) {
        doubleTotalRupees += 19.99;
        exactPaiseTotal += 1999;
    }
    double exactRupees = static_cast<double>(exactPaiseTotal) / 100.0;
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Exact integer-paise total : Rs " << exactRupees << "\n";
    std::cout << "Accumulated double total  : Rs " << doubleTotalRupees << "\n";
    std::cout << "Accumulated error         : Rs " << (doubleTotalRupees - exactRupees) << "\n";
    return 0;
}
