# Task 2 – Use Tokens, Keywords, Identifiers and Constants Correctly (3 Marks)

## 1. Five Kinds of C++ Tokens in the Program
1. **Keywords**: `enum`, `class`, `constexpr`, `int`, `long`, `bool`, `if`, `return`, `static_assert`.
2. **Identifiers**: `Zone`, `BASE_FARE_PAISE`, `PEAK_SURCHARGE_PERCENT`, `MIN_POST_TRIP_BALANCE_PAISE`, `computeFarePaise`.
3. **Constants (Literals)**: `1000`, `2000`, `3000`, `20`, `5000`, `true`, `"Inner"`.
4. **Operators**: `=`, `+`, `+=`, `*`, `/`, `!=`, `==`, `<<`, `static_cast`.
5. **Punctuators (Separators)**: `;`, `{`, `}`, `(`, `)`, `[`, `]`, `,`, `::`.

## 2. `#define` vs. `const` vs. `constexpr`
- **`#define`**: Preprocessor text substitution before compilation. Has no type, ignores namespace/block scope, cannot be inspected easily in debuggers, and causes subtle operator-precedence bugs.
- **`const`**: Typed and scoped, but its value may be initialized at runtime (e.g., from user input), so it cannot always be used in array bounds or `static_assert`.
- **`constexpr`**: Guaranteed compile-time constant expression. Strongly typed, scoped, usable in `static_assert` and array dimensions, and folded directly into machine instructions with zero runtime overhead. **Preferred for the metro fare table.**

## 3. `enum` vs. `enum class`
- Unscoped `enum Zone { Inner, Middle, Outer };` leaks enumerators into the enclosing scope and implicitly converts to `int` (allowing nonsensical expressions like `Zone::Inner + 5` or accidental comparison with `Hour`).
- Scoped `enum class Zone { Inner, Middle, Outer };` keeps enumerators inside `Zone::` and forbids implicit conversion to `int`, preventing accidental mixing of zone IDs with integers.

## 4. Naming Rules & Conventions
- **C++ Rules**: Must start with a letter or underscore, contain only `[A-Za-z0-9_]`, cannot be a reserved keyword, and must not start with double underscores (`__`) or an underscore followed by an uppercase letter.
- **Project Conventions**:
  - `UPPER_SNAKE_CASE` for `constexpr` constants (`MIN_POST_TRIP_BALANCE_PAISE`).
  - `PascalCase` for types/classes/enums (`Zone`, `SmartCard`, `ConcessionType`).
  - `camelCase` for functions and local variables (`computeFarePaise`, `sampleOuterPeakFare`).

## 5. Alternative Concept & Complexity Analysis
- **Alternative**: Defining fares with `#define INNER_FARE 1000` macros and unscoped `enum`.
- **Type Checking & Scope**: `#define` bypasses C++ type checking and pollutes the global preprocessor namespace across all included headers, risking silent collisions. `constexpr` and `enum class` enforce strict type safety and lexical scoping.
- **Memory & Running Time**: Both `#define` and `constexpr` values are inlined as immediate operands by the compiler, occupying **0 bytes** of runtime data storage ($O(1)$ space) and executing in identical $O(1)$ CPU cycles.
