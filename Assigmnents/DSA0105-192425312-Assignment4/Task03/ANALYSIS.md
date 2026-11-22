# Task 3 – Constructors in Derived Classes and Member Classes (9 Marks)

## 1. Predict the Output Analysis (`Car` Snippet)
- **Output**: `Vehicle Engine Car | ~Car ~Engine ~Vehicle `
- **Explanation**:
  - **Construction Order**: Base classes are constructed first (`Vehicle`), followed by member objects (`Engine e`), and finally the derived class body (`Car`).
  - **Destruction Order**: Exactly reverse of construction — derived class destructor (`~Car`), member destructors (`~Engine`), and finally base class destructor (`~Vehicle`).

## 2. Complete the Code Verification
- `Student` constructor correctly delegates parameters to `Person(n, a)`, initializes `regNo`, and constructs member `home(c, p)` via member initializer list.
