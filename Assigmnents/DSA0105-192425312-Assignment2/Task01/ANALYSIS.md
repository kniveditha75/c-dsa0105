# Q1 – Call by Value, by Reference and by Pointer (6 Marks)

## 1. Predict the Output Analysis
- **`change(a, b, &c);` output $\to$ `1 12 13`**:
  - `a` is passed by value (local copy modified, caller `a` remains `1`).
  - `b` is passed by reference (caller `b` incremented by 10 $\to$ `12`).
  - `c` is passed by pointer address `&c` (dereferenced `*c` incremented by 10 $\to$ `3 + 10 = 13`).
- **`bigger(a, c) = 100;` output $\to$ `1 100`**:
  - `bigger` returns a reference to the larger of `a` (`1`) and `c` (`13`), which is `c`. Assigning `100` to this reference mutates caller variable `c` to `100`. `a` remains `1`.
- **`show()` calls $\to$ `16 13 6`**:
  - `show(1)` uses default arguments `y=5`, `z=10` $\to$ `1 + 5 + 10 = 16`.
  - `show(1, 2)` uses default argument `z=10` $\to$ `1 + 2 + 10 = 13`.
  - `show(1, 2, 3)` uses no default arguments $\to$ `1 + 2 + 3 = 6`.

## 2. Complete the Code Verification
- `applyByValue` modifies only the function stack's local copy, leaving `hostelFee` at `45000`.
- `applyConcession` takes `long long& fee` by reference, mutating the caller's variable in place to `40500`.

## 3. Alternative Concept & Complexity Analysis
- **Alternative**: Returning the new fee (`long long applyConcession(long long fee, int percent)`) by value instead of reference.
- **Time Complexity**: $O(1)$ in all versions (a few arithmetic operations).
- **Space Copied**: Passing a primitive `long long` (8 bytes) by value incurs 8 bytes copy overhead. Passing a large `Student` object (e.g., 1KB) by value copies 1KB per call, whereas passing by reference (`const Student&`) passes a single 8-byte pointer with zero copy overhead.
