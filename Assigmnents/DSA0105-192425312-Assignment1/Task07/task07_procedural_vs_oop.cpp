#include <iostream>
#include <string>

// Task 7: Procedural Style vs. Object-Oriented Style (SmartCard Class)

enum class Zone { Inner = 0, Middle = 1, Outer = 2 };
constexpr long long BASE_PAISE[3] = {1000, 2000, 3000};
constexpr long long MIN_BALANCE_PAISE = 5000;

long long computeFare(Zone z, bool peak) {
    long long f = BASE_PAISE[static_cast<int>(z)];
    return peak ? f + (f * 20) / 100 : f;
}

// ==========================================
// 1. PROCEDURAL VERSION (Free functions + raw variables)
// ==========================================
bool procCanTravel(long long balance, long long fare) {
    return (balance - fare) >= MIN_BALANCE_PAISE;
}

bool procDeduct(long long& balance, long long fare) {
    if (!procCanTravel(balance, fare)) return false;
    balance -= fare;
    return true;
}

// ==========================================
// 2. OBJECT-ORIENTED VERSION (Encapsulated SmartCard)
// ==========================================
class SmartCard {
private:
    std::string cardId;
    long long balancePaise;
    static constexpr long long MIN_REMAINING_PAISE = 5000;

public:
    SmartCard(std::string id, long long initialPaise)
        : cardId(id), balancePaise(initialPaise >= 0 ? initialPaise : 0) {}

    bool canTravel(long long farePaise) const {
        return farePaise > 0 && (balancePaise - farePaise) >= MIN_REMAINING_PAISE;
    }

    bool deduct(long long farePaise) {
        if (!canTravel(farePaise)) return false;
        balancePaise -= farePaise;
        return true;
    }

    long long balance() const { return balancePaise; }
    const std::string& id() const { return cardId; }
};

int main() {
    std::cout << "=== TASK 7: PROCEDURAL VS OBJECT-ORIENTED COMPARISON ===\n\n";

    // Procedural test
    long long procBalance = 8000; // Rs 80
    long long f1 = computeFare(Zone::Outer, true); // Rs 36 -> leaves Rs 44 (< 50)
    std::cout << "[Procedural] Initial: " << procBalance << " paise | Trip fare: " << f1 << "\n";
    std::cout << "[Procedural] Deduct result: " << std::boolalpha << procDeduct(procBalance, f1)
              << " | Balance: " << procBalance << "\n";
    // Vulnerability in procedural style: nothing prevents accidental direct mutation!
    // procBalance -= 9000; // Would create -1000 negative balance!

    std::cout << "\n";

    // OOP test
    SmartCard card("NM-7001", 8000);
    std::cout << "[OOP SmartCard] Initial: " << card.balance() << " paise | Trip fare: " << f1 << "\n";
    std::cout << "[OOP SmartCard] Deduct result: " << std::boolalpha << card.deduct(f1)
              << " | Balance: " << card.balance() << "\n";

    long long f2 = computeFare(Zone::Middle, false); // Rs 20 -> leaves Rs 60 (>= 50)
    std::cout << "[OOP SmartCard] Trip 2 fare: " << f2
              << " | Deduct result: " << card.deduct(f2)
              << " | Balance: " << card.balance() << "\n";
    return 0;
}
