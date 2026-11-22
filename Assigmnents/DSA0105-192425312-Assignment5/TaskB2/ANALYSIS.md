# Task B2 – Engineer Error Conditions (5 Marks)

## 1. Output Prediction Analysis (`validate` / `process` Snippet)
- Validating amounts `100.0`, `-5.0`, and `2e6` demonstrates catch handling of `std::invalid_argument` and `std::out_of_range`. Re-throwing with `throw;` preserves the exact polymorphic exception type without object slicing (which `throw e;` would cause).

## 2. Complete the Code Verification
- `approve()` correctly checks for negative values and excess claims. `settle()` catches `ClaimError`, logs `"audit: "`, and rethrows with `throw;`. Expected output verified.
