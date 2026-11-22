#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

// Task 9: Complete Fare Logic & Automated Boundary/Invalid Test Suite

enum class Zone { Inner = 0, Middle = 1, Outer = 2, Invalid = -1 };
enum class PassengerType { Regular, Student, Senior };

class MetroGateSystem {
private:
    static constexpr long long BASE_PAISE[3] = {1000, 2000, 3000};
    static constexpr int PEAK_PCT = 20;
    static constexpr int CONCESSION_PCT = 25;
    static constexpr long long MIN_BALANCE_PAISE = 5000;

public:
    static bool isPeak(int hour) {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    static long long computeFare(Zone z, int hour, PassengerType p) {
        if (z == Zone::Invalid || static_cast<int>(z) < 0 || static_cast<int>(z) > 2) return -1;
        if (hour < 0 || hour > 23) return -1;
        long long f = BASE_PAISE[static_cast<int>(z)];
        if (isPeak(hour)) f += (f * PEAK_PCT) / 100;
        if (p == PassengerType::Student || p == PassengerType::Senior) {
            f -= (f * CONCESSION_PCT) / 100;
        }
        return f;
    }

    static bool processTrip(long long& balancePaise, Zone z, int hour, PassengerType p, long long& chargedOut) {
        long long f = computeFare(z, hour, p);
        if (f < 0) {
            chargedOut = 0;
            return false;
        }
        if ((balancePaise - f) < MIN_BALANCE_PAISE) {
            chargedOut = f;
            return false;
        }
        balancePaise -= f;
        chargedOut = f;
        return true;
    }

    static bool recharge(long long& balancePaise, long long amountPaise) {
        if (amountPaise <= 0) return false;
        balancePaise += amountPaise;
        return true;
    }
};

struct TestCase {
    std::string name;
    long long startBal;
    Zone zone;
    int hour;
    PassengerType pType;
    bool expectedApproved;
    long long expectedFare;
    long long expectedEndBal;
};

int main() {
    std::cout << "=== TASK 9: COMPLETE FARE LOGIC & TEST SUITE ===\n\n";

    std::vector<TestCase> tests = {
        {"1. Inner Off-Peak Regular",      10000, Zone::Inner,   11, PassengerType::Regular, true,  1000, 9000},
        {"2. Middle Peak Regular",         10000, Zone::Middle,   9, PassengerType::Regular, true,  2400, 7600},
        {"3. Outer Peak Student (25% off)",10000, Zone::Outer,   18, PassengerType::Student, true,  2700, 7300},
        {"4. Boundary 08:00 (Peak start)", 10000, Zone::Inner,    8, PassengerType::Regular, true,  1200, 8800},
        {"5. Boundary 10:00 (Peak end)",   10000, Zone::Inner,   10, PassengerType::Regular, true,  1000, 9000},
        {"6. Boundary 17:00 (Eve start)",  10000, Zone::Middle,  17, PassengerType::Regular, true,  2400, 7600},
        {"7. Boundary 20:00 (Eve end)",    10000, Zone::Middle,  20, PassengerType::Regular, true,  2000, 8000},
        {"8. Exact Rs 50 residual bal",     6000, Zone::Inner,   14, PassengerType::Regular, true,  1000, 5000},
        {"9. Rs 49.99 residual (Denied)",   5999, Zone::Inner,   14, PassengerType::Regular, false, 1000, 5999},
        {"10. Invalid Zone (-1)",          10000, Zone::Invalid, 10, PassengerType::Regular, false,    0, 10000},
        {"11. Invalid Hour (25)",          10000, Zone::Inner,   25, PassengerType::Regular, false,    0, 10000}
    };

    int passed = 0;
    for (const auto& tc : tests) {
        long long bal = tc.startBal;
        long long charged = 0;
        bool approved = MetroGateSystem::processTrip(bal, tc.zone, tc.hour, tc.pType, charged);
        bool ok = (approved == tc.expectedApproved) && (charged == tc.expectedFare) && (bal == tc.expectedEndBal);
        if (ok) ++passed;
        std::cout << (ok ? "[PASS] " : "[FAIL] ") << std::left << std::setw(34) << tc.name
                  << " | Exp Fare=" << std::setw(4) << tc.expectedFare
                  << " Act Fare=" << std::setw(4) << charged
                  << " | EndBal=" << bal << "\n";
    }

    // Negative recharge check
    long long testBal = 5000;
    bool negRechargeOk = MetroGateSystem::recharge(testBal, -500);
    std::cout << (!negRechargeOk && testBal == 5000 ? "[PASS] " : "[FAIL] ")
              << "12. Negative recharge rejected (Balance unchanged: " << testBal << ")\n";
    if (!negRechargeOk && testBal == 5000) ++passed;

    // Hand-calculated 5-journey batch
    std::cout << "\n--- Hand-Calculated 5-Journey Batch (Start: Rs 200.00 = 20000 paise) ---\n";
    long long batchBal = 20000;
    long long totalCollected = 0;
    struct BatchItem { Zone z; int h; PassengerType p; };
    BatchItem batch[5] = {
        {Zone::Inner,  8, PassengerType::Regular}, // 1000 + 20% = 1200
        {Zone::Middle, 10, PassengerType::Regular}, // 2000 (off-peak)
        {Zone::Outer,  17, PassengerType::Regular}, // 3000 + 20% = 3600
        {Zone::Outer,  20, PassengerType::Student}, // 3000 - 25% = 2250
        {Zone::Middle, 19, PassengerType::Senior}   // 2400 - 25% = 1800
    };
    for (int i = 0; i < 5; ++i) {
        long long f = 0;
        MetroGateSystem::processTrip(batchBal, batch[i].z, batch[i].h, batch[i].p, f);
        totalCollected += f;
    }
    std::cout << "Hand-calculated total: 1200 + 2000 + 3600 + 2250 + 1800 = 10850 paise (Rs 108.50)\n";
    std::cout << "Program total        : " << totalCollected << " paise (Rs " << totalCollected / 100 << "." << totalCollected % 100 << ")\n";
    std::cout << "Remaining balance    : " << batchBal << " paise (Rs " << batchBal / 100 << "." << batchBal % 100 << ")\n";
    std::cout << "\nSummary: " << passed << "/12 automated tests passed.\n";
    return 0;
}
