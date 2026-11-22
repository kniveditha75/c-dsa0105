#include <iostream>
#include <iomanip>
#include <string>

// Task 12: Day-4 Design Challenge (8 Marks)
// Requirements:
// 1. Fourth zone: Airport (Rs 60 = 6000 paise)
// 2. 10% weekend discount that does NOT combine with peak surcharge
// 3. Monthly pass allowing unlimited journeys in two chosen zones

enum class Zone : int { Inner = 0, Middle = 1, Outer = 2, Airport = 3, Count = 4 };
enum class PassengerType { Regular, Student, Senior };

class TariffEngine {
private:
    static constexpr long long BASE_PAISE[4] = {1000, 2000, 3000, 6000}; // Inner, Middle, Outer, Airport
    static constexpr int PEAK_SURCHARGE_PCT = 20;
    static constexpr int WEEKEND_DISCOUNT_PCT = 10;
    static constexpr int CONCESSION_PCT = 25;

public:
    static bool isPeakHour(int hour) {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    static long long calculateFarePaise(Zone z, int hour, bool isWeekend, PassengerType pType) {
        int idx = static_cast<int>(z);
        if (idx < 0 || idx >= static_cast<int>(Zone::Count) || hour < 0 || hour > 23) return -1;

        long long fare = BASE_PAISE[idx];

        // Rule: Weekend 10% discount does NOT combine with peak surcharge
        if (isWeekend) {
            fare -= (fare * WEEKEND_DISCOUNT_PCT) / 100;
        } else if (isPeakHour(hour)) {
            fare += (fare * PEAK_SURCHARGE_PCT) / 100;
        }

        // Apply student/senior concession if applicable
        if (pType == PassengerType::Student || pType == PassengerType::Senior) {
            fare -= (fare * CONCESSION_PCT) / 100;
        }
        return fare;
    }
};

class MonthlyPass {
private:
    bool active;
    Zone allowedZone1;
    Zone allowedZone2;

public:
    MonthlyPass() : active(false), allowedZone1(Zone::Inner), allowedZone2(Zone::Inner) {}
    MonthlyPass(Zone z1, Zone z2) : active(true), allowedZone1(z1), allowedZone2(z2) {}

    bool coversZone(Zone z) const {
        return active && (z == allowedZone1 || z == allowedZone2);
    }
};

class SmartCard {
private:
    std::string cardId;
    PassengerType holderType;
    long long balancePaise;
    MonthlyPass pass;
    static constexpr long long MIN_RESIDUAL_PAISE = 5000;

public:
    SmartCard(std::string id, PassengerType type, long long initialPaise, MonthlyPass p = MonthlyPass())
        : cardId(std::move(id)), holderType(type),
          balancePaise(initialPaise >= 0 ? initialPaise : 0), pass(p) {}

    bool processJourney(Zone z, int hour, bool isWeekend) {
        if (pass.coversZone(z)) {
            std::cout << "[PASS-FREE] Card " << cardId << " | Zone covered by Monthly Pass | Fare: Rs 0.00"
                      << " | Balance: Rs " << balancePaise / 100 << "." << std::setw(2) << std::setfill('0') << balancePaise % 100 << std::setfill(' ') << "\n";
            return true;
        }

        long long fare = TariffEngine::calculateFarePaise(z, hour, isWeekend, holderType);
        if (fare < 0 || (balancePaise - fare) < MIN_RESIDUAL_PAISE) {
            std::cout << "[DENIED]    Card " << cardId << " | Fare: Rs " << fare / 100 << "." << std::setw(2) << std::setfill('0') << fare % 100 << std::setfill(' ')
                      << " | Balance: Rs " << balancePaise / 100 << "." << std::setw(2) << std::setfill('0') << balancePaise % 100 << std::setfill(' ') << "\n";
            return false;
        }

        balancePaise -= fare;
        std::cout << "[APPROVED]  Card " << cardId << " | Fare: Rs " << fare / 100 << "." << std::setw(2) << std::setfill('0') << fare % 100 << std::setfill(' ')
                  << " | Balance: Rs " << balancePaise / 100 << "." << std::setw(2) << std::setfill('0') << balancePaise % 100 << std::setfill(' ') << "\n";
        return true;
    }
};

int main() {
    std::cout << "=== TASK 12: DAY-4 DESIGN CHALLENGE VERIFICATION ===\n\n";

    // Card 1: Regular stored-value card (Rs 150.00)
    SmartCard regular("NM-8001", PassengerType::Regular, 15000);
    // 1. Airport on Weekday Peak (9 AM): Rs 60 + 20% = Rs 72.00 -> Bal Rs 78.00
    regular.processJourney(Zone::Airport, 9, false);
    // 2. Airport on Weekend Peak (9 AM): 10% discount ONLY (no peak surcharge!) -> Rs 60 - 10% = Rs 54.00 -> Bal Rs 24 (< 50) -> Denied!
    regular.processJourney(Zone::Airport, 9, true);
    // 3. Outer on Weekend Peak (18 PM): Rs 30 - 10% = Rs 27.00 -> Bal 78 - 27 = Rs 51.00 (>= 50) -> Approved!
    regular.processJourney(Zone::Outer, 18, true);

    std::cout << "\n";
    // Card 2: Monthly Pass covering Inner & Airport, with Rs 60.00 stored value
    MonthlyPass airportPass(Zone::Inner, Zone::Airport);
    SmartCard passHolder("NM-9002", PassengerType::Regular, 6000, airportPass);
    passHolder.processJourney(Zone::Airport, 9, false);  // Covered by pass -> Rs 0.00!
    passHolder.processJourney(Zone::Inner, 18, false);   // Covered by pass -> Rs 0.00!
    passHolder.processJourney(Zone::Outer, 14, false);   // Not covered -> Rs 30.00 -> leaves Rs 30 (< 50) -> Denied!
    return 0;
}
