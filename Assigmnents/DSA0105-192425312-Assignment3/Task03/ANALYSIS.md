# Q3 – Dynamic Constructors and Destructors (7 Marks)

## 1. Predict the Output Analysis (`Logger`)
- **Output**: `+A +B -B copyAc use -Ac +P -P end -A `
- **Explanation**:
  1. `Logger a("A")` $\to$ `+A`.
  2. Inner block creates `b("B")` (`+B`) and destroys it immediately at `}` (`-B`).
  3. `use(a)` passes `a` by value, invoking copy constructor (`copyAc`), prints `use `, then destroys the parameter copy at function return (`-Ac`).
  4. `new Logger("P")` allocates on heap (`+P`), `delete p` destroys it (`-P`).
  5. Prints `end `, then `main()` exits and destroys stack object `a` (`-A`).

## 2. Memory Management & RAII
- Forgetting `delete` leaks heap memory (detected by `-fsanitize=address`). Using `delete` instead of `delete[]` for an array causes undefined behaviour and fails to invoke destructors for elements `1..n-1`.
- Destructors take no arguments and cannot be overloaded because destruction is invoked automatically by the runtime when objects leave scope.

## 3. Alternative Concept & Complexity Analysis
- **Alternative**: Flattened 1D allocation (`new char[rows * seats]` indexed via `r * seats + s`) or `std::vector<std::vector<char>>`.
- **Complexity**: Access time is **$O(1)$** in all designs. A 2D pointer array requires **`rows + 1` heap allocations** and `rows * sizeof(char*)` extra pointer space, whereas a flattened 1D block requires only **1 contiguous heap allocation** with zero row-pointer overhead and superior CPU cache locality.
