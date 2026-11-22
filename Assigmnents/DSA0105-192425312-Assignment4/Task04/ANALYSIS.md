# Task 4 – Pointers to Derived Classes: Forensics (7 Marks)

## 1. Predict the Output Analysis
- **Output**: `3.5 4.0 3.5`
- **Explanation**:
  - `p->rate()` prints `3.5` because `rate()` is non-virtual and resolved at compile time using pointer type `Account*`.
  - `p->vrate()` prints `4.0` because `vrate()` is virtual, resolving dynamically at runtime to `SeniorAccount::vrate()`.
  - `copy.vrate()` prints `3.5` because assigning `SeniorAccount s` to `Account copy` triggers **object slicing**, discarding the derived part and copying only the base `Account` portion.

## 2. Task 4.1 & 4.3 – Defect Analysis & Repair
- **Defects**: Non-virtual functions prevent dynamic dispatch; non-virtual base destructor causes memory leaks when deleting derived objects through base pointers; object slicing drops derived state.
- **Repair**: Added `virtual` keyword to member functions and destructor. Replaced raw management with `std::unique_ptr<Account>` or proper virtual destructors.
