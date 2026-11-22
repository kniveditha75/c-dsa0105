#include <iostream>

// Task 4: Predict the Output + Safe Explicit Conversions

int main()
{
    std::cout << "--- Given Program Output ---\n";
    int a = 7, b = 2;
    double c = a / b;
    double d = static_cast<double>(a) / b;
    std::cout << c << ' ' << d << '\n';

    char ch = 'A' + 2;
    std::cout << ch << ' ' << ch + 1 << '\n';

    bool flag = 5;
    std::cout << flag << ' ' << std::boolalpha << flag << '\n';

    unsigned int u = 1;
    int s = -1;
    std::cout << (s < u ? "s < u" : "s >= u") << '\n';

    std::cout << "\n--- Safe Alternative (Brace Init + static_cast) ---\n";
    int a2{7}, b2{2};
    double c2{static_cast<double>(a2) / static_cast<double>(b2)};
    char ch2{static_cast<char>('A' + 2)};
    bool flag2{5 != 0};
    int u_signed{1};
    int s2{-1};
    // int narrow{3.7}; // Compile-time error prevented by brace initialization!
    std::cout << "Exact division: " << c2 << ", char: " << ch2
              << ", flag: " << flag2 << ", signed cmp: " << (s2 < u_signed ? "s < u" : "s >= u") << '\n';
    return 0;
}
