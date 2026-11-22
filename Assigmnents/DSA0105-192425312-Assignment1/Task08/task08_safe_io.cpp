#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

// Task 8: Safe Input Reading (cin.fail, cin.clear, cin.ignore) and Formatted Output

enum class Zone { Inner = 0, Middle = 1, Outer = 2 };
constexpr long long BASE_PAISE[3] = {1000, 2000, 3000};
constexpr long long MIN_BALANCE_PAISE = 5000;

int readIntSafe(const std::string& prompt, int minVal, int maxVal) {
    int value{};
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= minVal && value <= maxVal) {
                return value;
            }
            std::cout << "  [Error] Value out of range [" << minVal << ".." << maxVal << "]. Try again.\n";
        } else {
            if (std::cin.eof()) {
                std::cout << "\n  [EOF] Input stream ended.\n";
                return minVal;
            }
            std::cout << "  [Error] Invalid non-numeric input! Clearing buffer...\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void printPaise(long long paise) {
    std::cout << "Rs " << std::setw(4) << (paise / 100) << '.'
              << std::setw(2) << std::setfill('0') << (paise % 100)
              << std::setfill(' ');
}

int main() {
    std::cout << "=== TASK 8: SAFE GATE I/O & FORMATTED REPORT ===\n";
    long long balance = 12000; // Rs 120.00
    int n = readIntSafe("Enter number of journeys (1-5): ", 1, 5);

    std::cout << "\n-----------------------------------------------------------------\n";
    std::cout << std::left << std::setw(6) << "Trip"
              << std::setw(10) << "Zone"
              << std::setw(8) << "Hour"
              << std::setw(14) << "Fare"
              << std::setw(12) << "Status"
              << "Balance\n";
    std::cout << "-----------------------------------------------------------------\n";

    const char* zNames[3] = {"Inner", "Middle", "Outer"};
    for (int i = 1; i <= n; ++i) {
        int zIdx = readIntSafe("Journey Zone (0=Inner, 1=Middle, 2=Outer): ", 0, 2);
        int hour = readIntSafe("Entry Hour (0-23): ", 0, 23);

        bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
        long long fare = BASE_PAISE[zIdx] + (peak ? (BASE_PAISE[zIdx] * 20) / 100 : 0);
        bool ok = (balance - fare) >= MIN_BALANCE_PAISE;
        if (ok) balance -= fare;

        std::cout << std::left << std::setw(6) << i
                  << std::setw(10) << zNames[zIdx]
                  << std::setw(2) << std::setfill('0') << std::right << hour << std::setfill(' ') << std::left << std::setw(6) << ":00";
        printPaise(fare);
        std::cout << "   " << std::setw(12) << (ok ? "APPROVED" : "DENIED");
        printPaise(balance);
        std::cout << "\n";
    }
    std::cout << "-----------------------------------------------------------------\n";
    return 0;
}
