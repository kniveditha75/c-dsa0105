# Q4 – Overloading Arithmetic and Stream Operators (7 Marks)

## 1. Operator Design & Rationale
- **`+` vs. `+=`**: Binary `+` must not mutate either operand, so it returns a new `Money` object by value. Compound `+=` mutates the left-hand operand in place and returns `Money&` (`*this`) to support chaining (`a += b += c`).
- **Why `<<` must be a non-member**: In `std::cout << m`, the left-hand operand is `std::ostream`, not `Money`. Since we cannot modify the standard library's `std::ostream` class to add a member function, `operator<<` must be a non-member `friend` function.
- **Why `long long paise` beats `double`**: Storing exact integer paise prevents IEEE-754 binary floating-point rounding drift over 1,000,000 additions (`Rs 10000.00` exact vs. floating-point drift). Multiplying `Money * Money` has no physical unit meaning (`Rs^2`), so only scalar multiplication (`Money * int`) should be permitted.

## 2. Alternative Concept & Complexity Analysis
- **Alternative**: Defining binary `operator+` as a non-member friend function (`friend Money operator+(const Money& lhs, const Money& rhs)`).
- **Complexity & Symmetry**: Both member and non-member `operator+` run in **$O(1)$ time** and **$O(1)$ space**. However, a non-member friend `operator+` allows implicit conversion on **both** operands, enabling symmetric expressions like `100 + m` (converting `100` via `Money(100)`) as well as `m + 100`, whereas a member `operator+` only supports `m + 100`.
