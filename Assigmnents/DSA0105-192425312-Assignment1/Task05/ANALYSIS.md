# Task 5 – Write Correct Expressions with the Right Precedence (4 Marks)

## 1. Metro Fare Expressions & Precedence Analysis
1. **Peak Check**:
   ```cpp
   bool isPeak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
   ```
   - Relational `>=`, `<` (precedence 9, left-to-right) bind tighter than logical `&&` (precedence 14), which binds tighter than logical `||` (precedence 15).
   - `hour >= 8 && hour < 10 || hour >= 17 && hour < 20` is syntactically equivalent because `&&` > `||`, but explicit parentheses prevent human misreading.
2. **Surcharge & Concession with Conditional Operator (`?:`) & Compound Assignment**:
   ```cpp
   fare += isPeak ? (fare * 20) / 100 : 0;
   fare -= isConcession ? (fare * 25) / 100 : 0;
   ```
   - Multiplicative `*` and `/` (left-to-right) compute `(fare * 20) / 100` before `?:` (precedence 16, right-to-left) selects the delta, and `+=` / `-=` (precedence 16, right-to-left) updates `fare`.

## 2. `x++` vs. `++x` and Undefined Behaviour in `i = i++`
- `++x` (pre-increment) increments `x` and evaluates to the **new** value (lvalue).
- `x++` (post-increment) increments `x` and evaluates to a copy of the **old** value (prvalue).
- `i = i++;` modifies `i` twice within the same full-expression without sequencing, causing **Undefined Behaviour (UB)** in C++.

## 3. Division `/` and Remainder `%` with Negative Operands
- Since C++11, integer `/` truncates toward zero (`-10 / 3 == -3`).
- Remainder satisfies `(a / b) * b + (a % b) == a`, so `-10 % 3 == -1` (sign matches the dividend).

## 4. Predict the Output (Written Before Execution)
**Predicted Output:**
```text
11 16
9 6 4
6 4
3 1 -3 -1
18
```
- **Line 1**: `*` > `+`: `5 + (3 * 2) = 11`; parentheses override: `(5 + 3) * 2 = 16`.
- **Line 2**: `x++` yields `5` (then `x` becomes `6`); `++y` increments `y` to `4` and yields `4`; `z = 5 + 4 = 9`. Output: `9 6 4`.
- **Line 3**: `6 > 4 ? 6 : 4` yields `6`. `%` and `*` have equal precedence and left-to-right associativity: `(6 % 4) * 2 = 2 * 2 = 4`. Output: `6 4`.
- **Line 4**: `10 / 3 = 3`, `10 % 3 = 1`, `-10 / 3 = -3`, `-10 % 3 = -1`.
- **Line 5**: `i` takes values `0, 3, 6, 9`; `k = 0 + 3 + 6 + 9 = 18`.

## 5. Alternative Concept & Complexity Analysis
- **Alternative**: Precomputed 24-element lookup table `constexpr bool PEAK_HOUR[24] = {0,0,0,0,0,0,0,0, 1,1, 0,0,0,0,0,0,0, 1,1,1, 0,0,0,0};` indexed via `PEAK_HOUR[hour]`.
- **Time Complexity**: **$O(1)$** in both, but `PEAK_HOUR[hour]` performs **1 array indexing operation** vs. up to **4 comparisons + 3 logical ops** in the boolean expression.
- **Space Complexity**: The lookup table uses **24 bytes** ($O(1)$ static memory), whereas the logical expression uses **0 bytes** of data storage.
