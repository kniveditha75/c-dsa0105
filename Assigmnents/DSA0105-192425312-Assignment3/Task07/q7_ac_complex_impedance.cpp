#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

// Q7: Design a Complex-Number Class from First Principles (AC Circuit Impedance Calculator)

class Complex {
    double re;
    double im;

public:
    // Constructors: default, from real part, and from real + imaginary parts
    Complex(double r = 0.0, double i = 0.0) : re(r), im(i) {}

    double real() const { return re; }
    double imag() const { return im; }
    double magnitude() const { return std::hypot(re, im); }

    Complex operator+(const Complex& o) const { return Complex(re + o.re, im + o.im); }
    Complex operator-(const Complex& o) const { return Complex(re - o.re, im - o.im); }

    Complex operator*(const Complex& o) const {
        return Complex(re * o.re - im * o.im, re * o.im + im * o.re);
    }

    Complex operator/(const Complex& o) const {
        double denom = o.re * o.re + o.im * o.im;
        if (denom < 1e-15) {
            throw std::domain_error("Division by zero AC impedance!");
        }
        return Complex((re * o.re + im * o.im) / denom,
                       (im * o.re - re * o.im) / denom);
    }

    bool operator==(const Complex& o) const {
        return std::abs(re - o.re) < 1e-9 && std::abs(im - o.im) < 1e-9;
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& z) {
        os << std::fixed << std::setprecision(2) << z.re
           << (z.im >= 0 ? " + " : " - ") << std::abs(z.im) << 'j';
        return os;
    }
};

int main() {
    std::cout << "=== Q7: AC CIRCUIT IMPEDANCE CALCULATOR ===\n";
    // R = 100 ohm, XL = +50j ohm, XC = -20j ohm
    Complex Zr(100.0);          // 100 + 0j
    Complex Zl(0.0, 50.0);      // 0 + 50j
    Complex Zc(0.0, -20.0);     // 0 - 20j

    // Series RLC: Z_series = Zr + Zl + Zc = 100 + 30j
    Complex Z_series = Zr + Zl + Zc;
    std::cout << "Series RLC Impedance   : " << Z_series
              << " | |Z| = " << Z_series.magnitude() << " ohm\n";

    // Parallel combination of Z1 = (100 + 0j) and Z2 = (0 + 100j):
    // (Z1 * Z2) / (Z1 + Z2) = (10000j) / (100 + 100j) = 50 + 50j
    Complex Z1(100.0, 0.0), Z2(0.0, 100.0);
    Complex Z_parallel = (Z1 * Z2) / (Z1 + Z2);
    std::cout << "Parallel Z1||Z2        : " << Z_parallel
              << " | |Z| = " << Z_parallel.magnitude() << " ohm\n";

    // Division by zero impedance safety check
    try {
        Complex zeroZ(0.0, 0.0);
        Complex bad = Z1 / zeroZ;
        std::cout << bad << '\n';
    } catch (const std::domain_error& e) {
        std::cout << "Safe Zero-Division Guard: " << e.what() << '\n';
    }
    return 0;
}
