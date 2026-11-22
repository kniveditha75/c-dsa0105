# Task 7 – From Procedural to Object-Oriented (4 Marks)

## 1. How `SmartCard` Prevents Negative Balances
- `balancePaise` is declared `private` inside `SmartCard`.
- The constructor clamps negative initial values (`initialPaise >= 0 ? initialPaise : 0`).
- `deduct(long long farePaise)` verifies `canTravel(farePaise)` (`farePaise > 0 && (balancePaise - farePaise) >= MIN_REMAINING_PAISE`) before subtracting. Because `MIN_REMAINING_PAISE = 5000 > 0`, `balancePaise` can **never** drop below Rs 50.00—let alone become negative.

## 2. Ease of Change When Minimum Balance Changes
- In the **OOP version**, `MIN_REMAINING_PAISE` is encapsulated inside `SmartCard`. Updating it from `5000` to `7500` requires changing **one line inside `SmartCard`**; all gate callers (`card.canTravel(f)` and `card.deduct(f)`) automatically inherit the new policy.
- In the **procedural version**, callers often inline `if (balance - fare >= 5000)` before calling `procDeduct`, forcing developers to audit every call site across the codebase.

## 3. Alternative Concept & Complexity Analysis
- **Alternative**: Making `balancePaise` a `public` member of `SmartCard` (`struct SmartCard { long long balancePaise; };`).
- **Time & Space Complexity**: **$O(1)$ time and $O(1)$ space** (8 bytes for `long long` + `std::string` header), identical to the `private` version.
- **Broken System Invariant**: Making `balancePaise` `public` destroys encapsulation—any module can write `card.balancePaise -= fare;` directly without calling `canTravel()`, violating both the **Rs 50 minimum residual balance rule** and the **non-negative balance invariant**.
