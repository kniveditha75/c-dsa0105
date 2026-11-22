#include <iostream>
#include <iomanip>

// Task 2: Tokens, Keywords, Identifiers, and Constants

enum class Zone { Inner = 0, Middle = 1, Outer = 2 };
enum class ConcessionType { None = 0, Student = 1, Senior = 2 };

constexpr int ZONE_COUNT = 3;
constexpr long long BASE_FARE_PAISE[ZONE_COUNT] = {1000, 2000, 3000}; // Rs 10, Rs 20, Rs 30
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int CONCESSION_PERCENT = 25;
constexpr long long MIN_POST_TRIP_BALANCE_PAISE = 5000; // Rs 50.00
constexpr int MORNING_PEAK_START = 8;
constexpr int MORNING_PEAK_END = 10;
constexpr int EVENING_PEAK_START = 17;
constexpr int EVENING_PEAK_END = 20;

// Compile-time check using constexpr
static_assert(BASE_FARE_PAISE[0] == 1000, "Inner zone fare must be 1000 paise");
static_assert(MIN_POST_TRIP_BALANCE_PAISE == 5000, "Minimum balance must be 5000 paise");

constexpr long long computeFarePaise(Zone zone, bool isPeak, ConcessionType concession) {
    long long fare = BASE_FARE_PAISE[static_cast<int>(zone)];
    if (isPeak) {
        fare += (fare * PEAK_SURCHARGE_PERCENT) / 100;
    }
    if (concession != ConcessionType::None) {
        fare -= (fare * CONCESSION_PERCENT) / 100;
    }
    return fare;
}

int main() {
    // Compile-time evaluated fare
    constexpr long long sampleOuterPeakFare = computeFarePaise(Zone::Outer, true, ConcessionType::None);
    static_assert(sampleOuterPeakFare == 3600, "Outer peak fare must be 3600 paise");

    std::cout << "=== TASK 2: CONSTANTS & ENUM CLASS VERIFICATION ===\n";
    const char* zoneNames[ZONE_COUNT] = {"Inner", "Middle", "Outer"};
    for (int i = 0; i < ZONE_COUNT; ++i) {
        Zone z = static_cast<Zone>(i);
        long long offPeak = computeFarePaise(z, false, ConcessionType::None);
        long long peak = computeFarePaise(z, true, ConcessionType::None);
        long long studentPeak = computeFarePaise(z, true, ConcessionType::Student);
        std::cout << std::left << std::setw(8) << zoneNames[i]
                  << " | Off-Peak: Rs " << offPeak / 100 << ".00"
                  << " | Peak: Rs " << peak / 100 << ".00"
                  << " | Student Peak: Rs " << studentPeak / 100 << ".00\n";
    }
    return 0;
}
