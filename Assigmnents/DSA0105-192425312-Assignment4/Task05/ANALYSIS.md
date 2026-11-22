# Task 5 – Pointers to Objects and the this Pointer (7 Marks)

## 1. Method Chaining & `this` Pointer Rationale
- `this` is a hidden pointer passed to every non-static member function pointing to the object on which the function was invoked. Returning `*this` by reference (`Cart&`) allows fluid **method chaining** (`c.add(...).add(...).setDiscount(...)`).
- Using `this->discount = discount;` explicitly resolves shadowing when parameter names match member names.

## 2. Complete the Code Verification
- `add()` stores items and returns `*this`. `setDiscount()` uses `this->discount` correctly. Expected output `324.00` verified.
