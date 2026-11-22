# Task 10 – Compare Expectations with Execution (4 Marks)

## 1. Observed Scaling Measurements (`20,000`, `500,000`, `3,000,000` Journeys)
- **`long long` paise** remains **100% exact** at every scale.
- **`double` rupees** accumulates floating-point rounding drift as $N$ grows because decimal values such as `23.33` cannot be represented finitely in IEEE-754 base-2 floating point.
- **32-bit `int` paise** succeeds at `20,000` and `500,000` journeys, but **overflows `INT_MAX` (`2,147,483,647`)** well before `3,000,000` journeys (~`6.93 billion` paise in the mixed workload, or `10.8 billion` paise at peak Outer fare), wrapping into a corrupt negative total.

## 2. Compiler Warnings with `-Wall -Wextra`
- Compiling early drafts with `-Wall -Wextra` surfaces:
  - `-Wsign-compare`: comparing `int` and `unsigned int` (resolved by using `int` / `long long` consistently).
  - `-Wconversion` / narrowing: assigning `double` to integer types without `static_cast` (resolved via integer-only paise arithmetic).
  - `-Wunused-parameter` / `-Wunused-variable`: caught and cleaned up.

## 3. Alternative Concept & Complexity Analysis
| Accumulator Type | Failure Mode at 3,000,000 Journeys | Time / Addition | Space / Variable |
| :--- | :--- | :---: | :---: |
| **`int` (paise)** | **Fails via Signed Overflow** at ~596,523 peak Outer trips (`> INT_MAX`), wrapping negative (Undefined Behaviour). | $O(1)$ | 4 bytes |
| **`long long` (paise)** | **Never fails** for any realistic metro network (`LLONG_MAX` $\approx 9.22 \times 10^{16}$ Rs). | $O(1)$ | 8 bytes |
| **`double` (rupees)** | **Fails via Precision Drift** (rounding error accumulates over millions of additions; loses exactness beyond $2^{53}$ units). | $O(1)$ | 8 bytes |
