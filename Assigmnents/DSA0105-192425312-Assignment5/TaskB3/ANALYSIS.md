# Task B3 – Virtual Functions vs Switch vs Exceptions: The Cost (8 Marks)

## 1. Benchmark & Complexity Analysis
- **Polymorphic Dispatch vs. Switch**: Virtual function calls incur a vtable pointer indirection ($O(1)$ time), which is slightly slower than direct `switch` dispatch due to instruction cache misses on highly branched tables. However, virtual functions decouple the caller from concrete types, enabling open-closed extensibility.
- **Exception Overhead**: Normal execution paths without exceptions have zero overhead. Throwing exceptions incurs stack unwinding overhead ($O(\text{stack depth})$), which is acceptable for exceptional error conditions but prohibitive in high-frequency inner loops.
