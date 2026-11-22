# Task 9 – Implement and Test the Fare Logic (4 Marks)

## 1. Test Matrix Summary
- **Normal Journeys**: Inner off-peak (`1000`), Middle peak (`2400`), Outer peak Student (`2700`).
- **Boundary Cases**:
  - `08:00` $\to$ Peak (`1200` paise).
  - `10:00` $\to$ Off-peak (`1000` paise — fixes v1 bug).
  - `17:00` $\to$ Peak (`2400` paise).
  - `20:00` $\to$ Off-peak (`2000` paise — fixes v1 bug).
  - Balance `6000` with `1000` fare $\to$ Approved, leaving exact `5000` paise (`Rs 50.00`).
  - Balance `5999` with `1000` fare $\to$ Denied (`4999 < 5000`).
- **Invalid Cases**: Zone `-1`, hour `25`, negative recharge `-500`, and non-numeric stream input (handled in Task 8).
- **5-Journey Hand-Calculated Batch**: $1200 + 2000 + 3600 + 2250 + 1800 = 10,850$ paise (`Rs 108.50`), leaving `9150` paise (`Rs 91.50`) from `Rs 200.00`.

## 2. Alternative Concept & Complexity Analysis
- **Alternative**: Data-driven table-driven test runner (`std::vector<TestCase>` iterated in a `for` loop) vs. separate hand-written `if/assert` statements for each case.
- **Time Complexity**: **$O(t)$** for $t$ test cases in both designs.
- **Space Complexity**: A `TestCase` table occupies **$O(t)$ memory** ($t \times \text{sizeof(TestCase)}$ bytes), whereas sequential hand-written calls use **$O(1)$ stack space**.
- **Maintainability**: Adding a new boundary case to a table-driven runner requires adding **1 struct initializer line** without duplicating assertion/printing boilerplate.
