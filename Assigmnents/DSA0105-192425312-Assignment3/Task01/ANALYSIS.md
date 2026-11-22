# Q1 – Constructors and Constructor Overloading (6 Marks)

## 1. Design & Analysis
- **Compiler Default Constructor**: Supplied implicitly only when no user-declared constructors exist. Once any parameterised constructor is declared, the compiler suppresses the implicit default constructor (causing `Book shelf[2];` to fail with `error: no matching function for call to 'Book::Book()'`).
- **Member Initializer Lists vs. Assignment**: Member initializer lists directly construct member objects in one step (`std::string` copy/move constructor), whereas assignment inside the constructor body first default-constructs members and then overwrites them. Also required for `const` and reference members.
- **Initialization Order**: Members are always initialized in the **order of their declaration inside the class**, regardless of their order in the member initializer list. Violating this triggers `-Wreorder`.
- **When to use `explicit`**: Single-argument constructors (like `explicit Book(const std::string& t)`) should be marked `explicit` to prevent unintended implicit conversions (e.g., passing `"Clean Code"` to a function expecting `Book`).

## 2. Alternative Concept & Complexity Analysis
- **Alternative**: A single constructor with default arguments (`Book(std::string t = "Untitled", std::string a = "Unknown", int c = 0)`).
- **Time & Space Complexity**: $O(1)$ time and $O(1)$ auxiliary space per object creation in both designs.
- **Validation Comparison**: Default arguments check `copies < 0` in only **one constructor body**, whereas overloaded constructors without delegation would duplicate validation across constructors (solved here via C++11 constructor delegation).
