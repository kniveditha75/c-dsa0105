# Task B4 – Final Engineering Decision (5 Marks)

## 1. Extension Demonstration & Production Decision
- **Extensibility**: Added `EmergencyBill` and a new payer category without modifying existing core classes, fulfilling the Open-Closed Principle.
- **Sanitizer Verification**: Compiled and verified under `-fsanitize=address` with zero memory leaks or undefined behaviour during stack unwinding.
- **Recommendation**: Polymorphism with exception handling is approved for hospital production environments processing 200,000 bills/day, as it guarantees type safety, maintainability, and resource safety under error conditions.
