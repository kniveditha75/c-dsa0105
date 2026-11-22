# Q2 – Return by Reference and Its Dangers (4 Marks)

## 1. Returning a Reference to Modify Elements
- Returning `int&` allows the caller to treat the function call as an lvalue (e.g., `getHighestMark(marks) += 2;`), directly modifying the underlying array/vector element without needing pointers or index lookups.

## 2. Dangling Reference Warning
- Returning a reference to a local variable (`int& bad() { int x = 10; return x; }`) causes the compiler to emit a warning (`warning: reference to local variable 'x' returned`). When the function returns, its stack frame is destroyed, leaving a **dangling reference** pointing to unallocated memory (Undefined Behaviour).

## 3. Vector Growth Invalidation
- When a `std::vector` grows beyond its capacity, it reallocates memory on the heap, copies elements to the new buffer, and frees the old memory. Any reference obtained before reallocation becomes **invalid** immediately. Using indices (`int idx`) or iterators with care avoids this.

## 4. Alternative Concept & Complexity Analysis
- **Alternative**: Returning an index (`int`) or pointer (`int*`).
- **Time & Space Complexity**: Finding the highest mark takes $O(n)$ time and $O(1)$ space in all designs.
- **Safety**: Returning an index (`int`) is safest when working with a growing `std::vector`, because reallocations invalidate pointers and references but do not invalidate integer index values.
