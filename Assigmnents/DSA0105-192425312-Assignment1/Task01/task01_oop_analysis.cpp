#include <iostream>
#include <string>
#include <iomanip>

// Task 1: Object-Oriented Analysis Demonstration
// Models SmartCard, Zone, FareTable, Passenger, and Journey for Namma Metro

enum class Zone { Inner = 0, Middle = 1, Outer = 2 };
enum class PassengerType { Regular, Student, SeniorCitizen };

class FareTable {
private:
    static constexpr long long BASE_PAISE[3] = {1000, 2000, 3000}; // Rs 10, 20, 30
    static constexpr int PEAK_SURCHARGE_PCT = 20;
    static constexpr int CONCESSION_PCT = 25; // 25% concession for Student/Senior

public:
    static bool isPeakHour(int hour) {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    static long long calculateFarePaise(Zone z, int hour, PassengerType pType) {
        long long fare = BASE_PAISE[static_cast<int>(z)];
        if (isPeakHour(hour)) {
            fare += (fare * PEAK_SURCHARGE_PCT) / 100;
        }
        if (pType == PassengerType::Student || pType == PassengerType::SeniorCitizen) {
            fare -= (fare * CONCESSION_PCT) / 100;
        }
        return fare;
    }
};

class SmartCard {
private:
    std::string cardId;
    PassengerType holderType;
    long long balancePaise;
    static constexpr long long MIN_REMAINING_PAISE = 5000; // Rs 50.00

public:
    SmartCard(std::string id, PassengerType type, long long initialPaise)
        : cardId(id), holderType(type), balancePaise(initialPaise >= 0 ? initialPaise : 0) {}

    bool canTravel(long long farePaise) const {
        return farePaise > 0 && (balancePaise - farePaise) >= MIN_REMAINING_PAISE;
    }

    bool deductFare(long long farePaise) {
        if (!canTravel(farePaise)) return false;
        balancePaise -= farePaise;
        return true;
    }

    void recharge(long long amountPaise) {
        if (amountPaise > 0) balancePaise += amountPaise;
    }

    long long getBalancePaise() const { return balancePaise; }
    PassengerType getHolderType() const { return holderType; }
    std::string getId() const { return cardId; }
};

class Journey {
private:
    Zone farthestZone;
    int hourOfDay;

public:
    Journey(Zone z, int hour) : farthestZone(z), hourOfDay(hour) {}

    bool process(SmartCard& card) const {
        if (hourOfDay < 0 || hourOfDay > 23) {
            std::cout << "[REJECTED] Invalid hour: " << hourOfDay << "\n";
            return false;
        }
        long long fare = FareTable::calculateFarePaise(farthestZone, hourOfDay, card.getHolderType());
        if (card.deductFare(fare)) {
            std::cout << "[APPROVED] Card " << card.getId()
                      << " | Fare: Rs " << fare / 100 << "." << std::setw(2) << std::setfill('0') << fare % 100
                      << " | Remaining: Rs " << card.getBalancePaise() / 100 << "." << std::setw(2) << card.getBalancePaise() % 100 << "\n";
            return true;
        } else {
            std::cout << "[DENIED]   Card " << card.getId()
                      << " | Required Fare: Rs " << fare / 100 << "." << std::setw(2) << std::setfill('0') << fare % 100
                      << " | Balance: Rs " << card.getBalancePaise() / 100 << "." << std::setw(2) << card.getBalancePaise() % 100
                      << " (Min Rs 50.00 post-trip rule)\n";
            return false;
        }
    }
};

int main() {
    std::cout << "=== TASK 1: OOP DOMAIN MODEL DEMONSTRATION ===\n";
    SmartCard regularCard("NM-1001", PassengerType::Regular, 10000);   // Rs 100.00
    SmartCard studentCard("NM-2002", PassengerType::Student, 7500);    // Rs 75.00

    Journey j1(Zone::Outer, 9);   // Peak hour (9 AM), Outer zone -> Rs 36.00
    Journey j2(Zone::Middle, 14); // Off-peak (2 PM), Middle zone -> Rs 20.00
    Journey j3(Zone::Outer, 18);  // Peak hour (6 PM), Outer zone -> Rs 36.00

    j1.process(regularCard); // 100 - 36 = 64 (>= 50) -> Approved
    j2.process(regularCard); // 64 - 20 = 44 (< 50) -> Denied!
    j3.process(studentCard); // 36 - 25% = 27.00 -> 75 - 27 = 48 (< 50) -> Denied!
    studentCard.recharge(1000); // Recharge Rs 10 -> 85.00
    j3.process(studentCard); // 85 - 27 = 58 (>= 50) -> Approved!
    return 0;
}
