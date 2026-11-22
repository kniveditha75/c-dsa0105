#include <iostream>
#include <iomanip>
#include <string>

// Task 11: Recommended Production Architecture for Namma Metro Gate Firmware

namespace NammaMetro {

enum class Zone : int { Inner = 0, Middle = 1, Outer = 2, Count = 3 };
enum class PassengerCategory : int { Regular = 0, Student = 1, Senior = 2 };

struct TariffConfig {
    static constexpr long long BASE_FARE_PAISE[3] = {1000, 2000, 3000};
    static constexpr int PEAK_SURCHARGE_PCT = 20;
    static constexpr int CONCESSION_PCT = 25;
    static constexpr long long MIN_RESIDUAL_PAISE = 5000;

    static constexpr bool isPeak(int hour) {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    static constexpr long long calculateFare(Zone z, int hour, PassengerCategory cat) {
        int idx = static_cast<int>(z);
        if (idx < 0 || idx >= static_cast<int>(Zone::Count) || hour < 0 || hour > 23) return -1;
        long long fare = BASE_FARE_PAISE[idx];
        if (isPeak(hour)) fare += (fare * PEAK_SURCHARGE_PCT) / 100;
        if (cat != PassengerCategory::Regular) fare -= (fare * CONCESSION_PCT) / 100;
        return fare;
    }
};

class SmartCard {
private:
    std::string id_;
    PassengerCategory category_;
    long long balancePaise_;

public:
    SmartCard(std::string id, PassengerCategory cat, long long initialPaise)
        : id_(std::move(id)), category_(cat), balancePaise_(initialPaise >= 0 ? initialPaise : 0) {}

    bool tapExit(Zone z, int hour, long long& fareCharged) {
        long long fare = TariffConfig::calculateFare(z, hour, category_);
        if (fare < 0 || (balancePaise_ - fare) < TariffConfig::MIN_RESIDUAL_PAISE) {
            fareCharged = 0;
            return false;
        }
        balancePaise_ -= fare;
        fareCharged = fare;
        return true;
    }

    long long balancePaise() const { return balancePaise_; }
};

} // namespace NammaMetro

int main() {
    using namespace NammaMetro;
    std::cout << "=== TASK 11: FINAL RECOMMENDED DESIGN VERIFICATION ===\n";
    SmartCard card("NM-PROD-01", PassengerCategory::Regular, 10000);
    long long charged = 0;
    if (card.tapExit(Zone::Outer, 9, charged)) {
        std::cout << "Tap 1 (Outer, 09:00 Peak) -> Charged: " << charged
                  << " paise | Remaining: " << card.balancePaise() << " paise\n";
    }
    if (!card.tapExit(Zone::Middle, 14, charged)) {
        std::cout << "Tap 2 (Middle, 14:00)     -> Blocked safely (Balance "
                  << card.balancePaise() << " paise protected)\n";
    }
    return 0;
}
