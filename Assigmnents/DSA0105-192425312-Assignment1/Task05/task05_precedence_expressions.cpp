#include <iostream>

// Task 5: Operator Precedence, Associativity, and Metro Expressions

bool isPeakHour(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

long long applyPeakSurcharge(long long basePaise, bool peak) {
    return peak ? (basePaise + (basePaise * 20) / 100) : basePaise;
}

long long applyConcession(long long farePaise, bool eligible) {
    return eligible ? (farePaise - (farePaise * 25) / 100) : farePaise;
}

int main() {
    std::cout << "--- Given Program Output ---\n";
    int x = 5, y = 3;
    std::cout << x + y * 2 << ' ' << (x + y) * 2 << '\n';

    int z = x++ + ++y;
    std::cout << z << ' ' << x << ' ' << y << '\n';

    std::cout << (x > y ? x : y) << ' ' << x % 4 * 2 << '\n';
    std::cout << 10 / 3 << ' ' << 10 % 3 << ' ' << -10 / 3 << ' ' << -10 % 3 << '\n';

    int k = 0;
    for (int i = 0; i < 10; i += 3) k += i;
    std::cout << k << '\n';

    std::cout << "\n--- Metro Expressions Verification ---\n";
    for (int h : {7, 8, 10, 17, 20}) {
        long long f = applyPeakSurcharge(3000, isPeakHour(h));
        std::cout << "Hour " << h << ":00 -> Peak=" << std::boolalpha << isPeakHour(h)
                  << " | Outer Fare=" << f << " paise\n";
    }
    return 0;
}
