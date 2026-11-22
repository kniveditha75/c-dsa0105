# Task 4 – Control Implicit Conversions (4 Marks)

## 1. Predict the Output (Written Before Execution)
**Predicted Output:**
```text
3 3.5
C 68
1 true
s >= u
```

## 2. Line-by-Line Explanation of Conversions
1. **`double c = a / b;` $\to$ `3` vs `double d = static_cast<double>(a) / b;` $\to$ `3.5`**:
   - Both `a` (`7`) and `b` (`2`) are `int`, so `a / b` performs **integer division**, truncating `3.5` to `3`. Only *after* division is `3` implicitly converted to `double` (`3.0`, printed as `3`).
   - In `d`, `static_cast<double>(a)` converts `a` to `7.0` first; usual arithmetic conversion promotes `b` to `2.0`, yielding `3.5`.
2. **`char ch = 'A' + 2;` and `std::cout << ch << ' ' << ch + 1;` $\to$ `C 68`**:
   - `'A'` (ASCII `65`) + `2` = `67`, narrowed to `char` `'C'`.
   - When `ch` is printed directly, `operator<<(ostream&, char)` prints the character `'C'`.
   - In `ch + 1`, **integral promotion** promotes `char` (`'C'`, 67) to `int` (`67 + 1 = 68`), so `operator<<(ostream&, int)` prints `68`.
3. **`bool flag = 5;` $\to$ `1 true`**:
   - Any non-zero `int` (`5`) implicitly converts to `bool` `true`.
   - By default `std::cout` prints `bool` as `1`; after `std::boolalpha`, it prints `true`.
4. **`unsigned int u = 1; int s = -1; (s < u ? "s < u" : "s >= u")` $\to$ `s >= u`**:
   - **Signed-to-unsigned conversion**: When comparing `int` and `unsigned int` of the same rank, `s` (`-1`) is implicitly converted to `unsigned int`, wrapping modulo $2^{32}$ to `4294967295` (`UINT_MAX`).
   - Since `4294967295 < 1` is `false`, the ternary evaluates to `"s >= u"`. Compiling with `-Wall -Wextra` emits `-Wsign-compare`.

## 3. Narrowing Conversions & Brace Initialization
- `int x = 3.7;` silently truncates `3.7` to `3`.
- Brace initialization `int x{3.7};` forbids narrowing conversions at compile time (emitting an error).

## 4. Alternative Concept & Complexity Analysis
- **Alternative**: Replacing all implicit conversions with explicit `static_cast<T>(...)` and uniform brace initialization `T var{...}`.
- **Time & Space Complexity**: **$O(1)$ time and $O(1)$ space** — `static_cast` and brace initialization generate the exact same machine instructions as implicit conversions with zero runtime overhead.
- **Compile-Time Error Detection**: Narrowing conversions (`double` $\to$ `int`, `long long` $\to$ `int`) and sign mismatches are caught at **compile time** rather than silently corrupting fares or balances at runtime.
