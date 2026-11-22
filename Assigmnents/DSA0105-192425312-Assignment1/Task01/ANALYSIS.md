# Task 1 – Understand the Problem and Identify the Objects (4 Marks)

## 1. Domain Objects, Data, and Behaviour
1. **`SmartCard`**:
   - **Data (Private)**: `cardId` (`std::string`), `holderType` (`PassengerType`), `balancePaise` (`long long`), `MIN_REMAINING_PAISE` (`5000`).
   - **Behaviour (Public)**: `canTravel(fare)`, `deductFare(fare)`, `recharge(amount)`, `getBalancePaise()`.
   - **Justification**: Encapsulating balance inside `SmartCard` guarantees the invariant (`balancePaise >= 5000` after any trip, never negative). No external module can mutate `balancePaise` directly.
2. **`Zone` & `PassengerType` (Value Types / Enumerations)**:
   - **Data**: `Zone { Inner, Middle, Outer }`, `PassengerType { Regular, Student, SeniorCitizen }`.
   - **Justification**: Prevents magic numbers (`0`, `1`, `2`) and invalid zone states via strong typing.
3. **`FareTable`**:
   - **Data**: `BASE_PAISE[] = {1000, 2000, 3000}`, `PEAK_SURCHARGE_PCT = 20`, `CONCESSION_PCT = 25`.
   - **Behaviour**: `isPeakHour(hour)`, `calculateFarePaise(zone, hour, passengerType)`.
   - **Justification**: Single source of truth for tariff rules, eliminating scattered literals from v1.
4. **`Journey`**:
   - **Data**: `farthestZone`, `hourOfDay`.
   - **Behaviour**: `process(SmartCard&)`.
   - **Justification**: Coordinates a single trip validation and atomic deduction between `FareTable` and `SmartCard`.

## 2. Procedural vs. Object-Oriented Style
- **Procedural Style**: Uses global arrays/variables (`long long balances[]`, `int baseFares[]`) and free functions (`deduct(cardIndex, fare)`). Any function anywhere in the program can modify `balances[i]`, causing the v1 negative-balance bug.
- **Object-Oriented Style**: Bundles state and invariant checks inside `SmartCard`. Outside code can only request `deductFare()`, which enforces the Rs 50 minimum post-journey rule atomically.

## 3. Four Pillars of OOP in the Metro System
- **Encapsulation**: `SmartCard::balancePaise` is `private`; mutations occur strictly through validated methods (`deductFare`, `recharge`).
- **Abstraction**: `Journey::process(card)` calls `FareTable::calculateFarePaise(...)` without needing to know how surcharges or concessions are computed internally.
- **Inheritance**: A base `FareRule` or `Card` class can be extended into `StudentCard`, `SeniorCard`, or `MonthlyPassCard`.
- **Polymorphism**: A virtual `computeFare(const Journey&)` method on a `DiscountPolicy` base class allows runtime dispatch for Regular, Student, Senior, or Weekend policies without modifying gate code.

## 4. Invariant Rules Every Correct Journey Must Satisfy
1. **Valid Zone**: `zone` must be one of the defined network zones (`Inner`, `Middle`, `Outer`).
2. **Valid Time**: `0 <= hour <= 23`. Peak hours are strictly half-open intervals `[8, 10)` and `[17, 20)` so 10:00 AM and 8:00 PM (20:00) are off-peak.
3. **Exact Arithmetic**: All monetary amounts are computed in integer paise (`1 Rs = 100 paise`) to prevent floating-point rounding drift.
4. **Minimum Residual Balance**: `balanceAfter >= 5000` paise (Rs 50.00) must hold before committing any deduction; balance can never become negative.

## 5. Alternative Concept & Complexity Analysis
- **Alternative**: Purely procedural design using global variables and free functions (`computeFare(zone, hour)` and `deduct(balance, fare)`).
- **Time Complexity**: $O(1)$ per journey in both designs (a fixed sequence of arithmetic and comparison operations).
- **Space Complexity**: $O(1)$ auxiliary space per journey and $O(1)$ (8 bytes for `long long` balance + ID) per card in both designs.
- **Maintainability / Code Change Impact**: In the procedural v1 design where fare literals and balance checks are duplicated across gate modules, changing one fare rule requires editing $K$ call sites ($O(K)$ code edits) and risks inconsistency. In the OOP design with `FareTable` and `SmartCard`, changing a fare or minimum balance requires editing **1 single constant** ($O(1)$ change).
