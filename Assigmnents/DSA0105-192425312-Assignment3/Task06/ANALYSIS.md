# Q6 – The Rules of Operator Overloading (7 Marks)

## 1. C++ Operator Overloading Rules
- **Non-Overloadable Operators**: `::` (scope resolution), `.` (member access), `.*` (pointer-to-member access), `?:` (ternary conditional), and `sizeof`. Overloading these would break fundamental compile-time type resolution and object layout semantics.
- **Fixed Rules**: Operator precedence, associativity, and arity (unary vs. binary) cannot be changed, and at least one operand must be a user-defined class or enum type.
- **Why `operator=` must be a member**: The C++ standard mandates `operator=` as a non-static member function so it cannot conflict with the compiler's implicitly generated copy/move assignment operators.

## 2. Alternative Concept & Complexity Analysis
- **Alternative**: Replacing custom `Text` with `std::string`, or implementing `operator+` via `operator+=` (`Text operator+(Text a, const Text& b) { a += b; return a; }`).
- **Complexity of `a + b + c`**: Evaluating `(a + b) + c` for lengths $n_1, n_2, n_3$ creates an intermediate temporary of size $n_1 + n_2$ (copying $n_1 + n_2$ bytes) and then allocates the final buffer of size $n_1 + n_2 + n_3$ (copying $(n_1 + n_2) + n_3$ bytes) — total **$O(n_1 + n_2 + n_3)$ time** and temporary heap allocation, whereas `std::string` avoids heap allocations for short messages via **Small String Optimization (SSO)**.
