# Task 3 – Choose Data Types and Check Type Compatibility (4 Marks)

## 1. Selected Data Types & System Sizes
| Domain Value | Chosen C++ Type | `sizeof` | Justification |
| :--- | :--- | :---: | :--- |
| Peak / Pass flag | `bool` | 1 byte | Binary state (`true`/`false`), self-documenting. |
| Zone code / delimiter | `char` | 1 byte | Single ASCII character (`'I'`, `'M'`, `'O'`). |
| Hour of day (`0..23`) | `int` | 4 bytes | Fast native word size; avoids signed/unsigned comparison bugs. |
| Zone index | `enum class Zone : int` | 4 bytes | Type-safe discrete domain (`Inner`, `Middle`, `Outer`). |
| Fare & Card Balance | `long long` (paise) | 8 bytes | Exact integer arithmetic; prevents rounding drift and overflow. |
| Daily journey count | `long long` | 8 bytes | Safely scales from 20,000 to 3,000,000+ journeys/day. |
| Concession / Surcharge % | `int` (integer math) | 4 bytes | Computed via `(fare * pct) / 100` without `float`/`double` error. |
| Type deduction | `auto` | Context | Used for iterators/structured bindings where type is obvious. |

## 2. Why Money Must Be Stored in Integer Paise (`long long`)
- Binary floating-point (`double`, IEEE-754 binary64) cannot represent decimal fractions like `0.10` or `19.99` exactly (`19.99` is stored as `19.9899999999999984368...`).
- Repeated additions accumulate ULP (Unit in the Last Place) rounding errors, causing fares or daily reconciliations to be off by paise or rupees, and breaking equality checks (`balance == 50.00`).
- Integer paise (`1000` for Rs 10.00) represent every rupee and paisa **with 100% mathematical exactness**.

## 3. Type Compatibility & Usual Arithmetic Conversions
- When `int`, `double`, and `bool` appear in the same expression:
  1. `bool` promotes to `int` (`false` $\to 0$, `true` $\to 1$).
  2. If any operand is `double`, the other `int` operand is implicitly converted to `double` before the operation.
  3. Assigning a `double` back to an `int` truncates the fractional part toward zero.

## 4. `<climits>` Ranges and Network Overflow Analysis
- **`INT_MAX` (32-bit `int`)**: `2,147,483,647` paise $\approx$ **Rs 21,474,836.47** (~Rs 2.14 Crore).
- **Whole Network Collection (3,000,000 journeys/day at Rs 36.00 peak Outer fare)**:
  $$3,000,000 \times 3,600\text{ paise} = 10,800,000,000\text{ paise} = \text{Rs } 108,000,000\text{ (Rs 10.8 Crore)}$$
- Since $10,800,000,000 > 2,147,483,647$ (`INT_MAX`), a 32-bit `int` **overflows** into negative numbers at network scale!
- **`LLONG_MAX` (64-bit `long long`)**: `9,223,372,036,854,775,807` paise ($\approx$ Rs $9.22 \times 10^{16}$), which never overflows.

## 5. Alternative Concept & Complexity Analysis
- **Alternative**: Storing money as `double` rupees instead of `long long` paise.
- **Time & Space Complexity**: Both `double` addition and `long long` addition take **$O(1)$ time** per operation and occupy **8 bytes ($O(1)$ space)** per variable.
- **Error Growth**: In `long long` paise, rounding error is strictly **0** for all $n$. In `double` rupees, each addition introduces up to $\frac{1}{2}\text{ulp} \approx 10^{-15}\cdot S$ rounding error, growing as $O(\sqrt{n})$ (random walk) to $O(n)$ (systematic bias, e.g., adding `19.99` $3\times 10^6$ times drifts by measurable paise/rupees).
