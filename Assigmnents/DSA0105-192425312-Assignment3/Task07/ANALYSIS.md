# Q7 – Design a Complex-Number Class from First Principles (10 Marks)

## 1. Four-Stage Engineering Design Summary
- **Stage 1 (Requirements)**: Model rectangular complex impedance $Z = R + jX$ supporting default (`0+0j`), pure resistive (`R+0j`), and general (`R+jX`) construction, series addition ($Z_1 + Z_2$), parallel combination $(Z_1 \times Z_2)/(Z_1 + Z_2)$, rectangular output formatting (`a + bj`), magnitude $|Z| = \sqrt{R^2 + X^2}$, and safe zero-denominator trapping.
- **Stage 2 (Design)**: `Complex` encapsulates two `double` fields (`re`, `im`), provides a single default-argument constructor `Complex(double r = 0.0, double i = 0.0)`, member arithmetic operators (`+`, `-`, `*`, `/`, `==`), and friend `operator<<`.
- **Stage 3 (Verification)**: Hand calculation for $Z_1 = 100 + 0j$ in parallel with $Z_2 = 0 + 100j$ yields $\frac{10000j}{100+100j} = 50 + 50j$ ($|Z| = 70.71\,\Omega$), matching program output identically. Division by $0+0j$ throws `std::domain_error`.
- **Stage 4 (Evaluation)**: Custom `Complex` prints engineering `j` notation directly and throws on zero division, whereas `std::complex<double>` prints `(re,im)` tuples and produces `NaN`/`Inf` silently on zero division.

## 2. Alternative Concept & Complexity Analysis
- **Alternative**: Using `std::complex<double>` from `<complex>`.
- **Complexity & Numerical Accuracy**: Both designs execute arithmetic in **$O(1)$ time** and **$O(1)$ space** (`16 bytes` for two `double` values). However, `std::complex<double>` uses Smith's algorithm in `operator/` to avoid intermediate overflow when `re*re + im*im` exceeds `DBL_MAX`, whereas our direct formula requires manual zero-checks (`denom < 1e-15`) to prevent `NaN`.
