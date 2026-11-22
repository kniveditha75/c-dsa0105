#include <iomanip>
#include <iostream>

// Q4: Overloading Arithmetic and Stream Operators (Money Arithmetic for Billing Counter)

class Money {
    long long paise;

public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    // TODO 1: Overload + as a member function that returns a new Money object
    Money operator+(const Money& rhs) const {
        Money res;
        res.paise = this->paise + rhs.paise;
        return res;
    }

    Money operator-(const Money& rhs) const {
        Money res;
        res.paise = this->paise - rhs.paise;
        return res;
    }

    Money& operator+=(const Money& rhs) {
        this->paise += rhs.paise;
        return *this;
    }

    bool operator<(const Money& rhs) const {
        return this->paise < rhs.paise;
    }

    // TODO 2: Overload == as a member, and << as a friend that prints "Rs 200.00"
    bool operator==(const Money& rhs) const {
        return this->paise == rhs.paise;
    }

    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        long long total = m.paise;
        if (total < 0) {
            os << "-";
            total = -total;
        }
        os << "Rs " << (total / 100) << '.' << std::setw(2) << std::setfill('0') << (total % 100);
        return os;
    }
};

int main() {
    std::cout << "=== Q4: MONEY ARITHMETIC & STREAM OPERATORS ===\n";
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';

    // Additional test: Paise carry into rupees (Rs 0.75 + Rs 0.50 = Rs 1.25)
    Money carryTest = Money(0, 75) + Money(0, 50);
    std::cout << "Carry test (0.75 + 0.50): " << carryTest << '\n';

    // Exactness check: 1,000,000 additions of Rs 0.01 (1 paisa)
    Money sum(0, 0);
    Money onePaisa(0, 1);
    for (int i = 0; i < 1000000; ++i) sum += onePaisa;
    std::cout << "1,000,000 x Rs 0.01 exact total: " << sum << '\n';
    return 0;
}
