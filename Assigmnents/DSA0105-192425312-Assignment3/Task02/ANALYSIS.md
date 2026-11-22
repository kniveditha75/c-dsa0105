# Q2 – Copy Constructors: Shallow and Deep Copies (7 Marks)

## 1. Shallow vs. Deep Copy & Rule of Three
- **Double Delete Crash**: Without a custom copy constructor, the compiler performs a member-wise **shallow copy**, duplicating the `medicines` pointer address. When both `p` and `q` go out of scope, `delete[] medicines` runs twice on the same heap address, causing undefined behaviour / `AddressSanitizer: attempting double-free`.
- **Rule of Three**: If a class manages a resource (raw heap pointer) and requires any one of **(1) Destructor**, **(2) Copy Constructor**, or **(3) Copy Assignment Operator**, it almost certainly requires all three.
- **Three Copy Constructor Situations**: (1) Initializing an object from another (`Prescription q = p;`), (2) Passing an object by value to a function, and (3) Returning an object by value (when not elided).

## 2. Alternative Concept & Complexity Analysis
- **Alternative (Rule of Zero)**: Using `std::vector<std::string> medicines` instead of raw `new[]`/`delete[]`.
- **Time & Space Complexity**: Deep copy (both custom `new[]` and `std::vector`) takes **$O(n)$ time** and **$O(n)$ heap space** to duplicate $n$ medicine strings. Shallow copy takes $O(1)$ time and $O(1)$ space but violates memory ownership safety.
