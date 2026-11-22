# Q5 – Overloading Increment, Comparison and Subscript Operators (6 Marks)

## 1. Predict the Output Analysis (`Counter`)
- **Output**: `5 7 7`
- **Explanation**: `c` starts at `5`. `a = c++` (postfix) makes a copy `old` (`5`), increments `c` to `6`, and assigns `5` to `a`. Then `b = ++c` (prefix) increments `c` in place to `7` and returns `*this` by reference, so both `b.v` and `c.v` are `7`.

## 2. Prefix vs. Postfix & `const` Subscript Overloading
- **Dummy `int`**: C++ distinguishes postfix `operator++(int)` from prefix `operator++()` via an unused `int` dummy parameter.
- **Why Prefer `++i` for Class Types**: Postfix `i++` must construct and return a temporary copy of the previous object state, whereas prefix `++i` mutates `*this` and returns a reference with zero copy overhead.
- **`const` vs. Non-`const` `operator[]`**: Non-`const` returns `T&` to allow mutation (`pl[0] = "New"`), while `const` returns `const T&` so read-only `const Playlist` objects can still be indexed.

## 3. Alternative Concept & Complexity Analysis
- **Alternative**: Unchecked `operator[]` (like C arrays) vs. bounds-checked `at(i)` throwing `std::out_of_range`.
- **Complexity**: Both take **$O(1)$ time** per access. Bounds checking adds a single integer comparison (`idx < 0 || idx >= size`), which is predicted cleanly by modern branch predictors with negligible nanosecond overhead while preventing silent buffer-overrun vulnerabilities.
