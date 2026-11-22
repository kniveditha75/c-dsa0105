# Task 12 – Day-4 Design Challenge: Re-evaluate and Adapt the Design (8 Marks)

## A. Impact Analysis (2 Marks)
Adding **Zone 4 (`Airport`, Rs 60)**, a **non-combining 10% weekend discount**, and a **2-zone Monthly Pass** impacts the original design as follows:
1. **Enum & Constants**: `enum class Zone` gains `Airport = 3` (`Count = 4`). `BASE_PAISE` expands from 3 to 4 elements (`{1000, 2000, 3000, 6000}`), and `WEEKEND_DISCOUNT_PCT = 10` is added.
2. **Expressions**: The fare formula must change from an independent `if (peak)` surcharge to a mutually exclusive branch (`if (isWeekend) ... else if (isPeakHour(hour)) ...`) so weekend trips never stack the 20% peak surcharge.
3. **`switch` Statements**: Any `switch (zone)` in Task 6 breaks or falls into `default:` unless updated with `case Zone::Airport:`. Array-indexed lookup (`BASE_PAISE[static_cast<int>(z)]`) absorbs the 4th zone automatically.
4. **Classes**: `SmartCard` alone cannot model unlimited zone-scoped pass travel without cluttering its state; introducing a cohesive `MonthlyPass` value/policy object composed inside `SmartCard` cleanly separates pass validity from stored-value deduction.

## B. Evaluation of the Original Design (2 Marks)
- **Decision**: **MODIFY (Targeted Refactoring)** — Retain the core `long long` paise representation, `enum class Zone`, and `SmartCard` invariant enforcement, while replacing `switch`-based fare lookup with table indexing and adding a `MonthlyPass` component.
- **Worked Examples**:
  1. *Airport Weekday Peak (09:00)*: `6000 + (6000 * 20)/100 = 7200` paise (`Rs 72.00`).
  2. *Airport Weekend Peak (09:00)*: Weekend suppresses peak surcharge $\to$ `6000 - (6000 * 10)/100 = 5400` paise (`Rs 54.00`).
  3. *Monthly Pass (`Inner`, `Airport`) at `Airport`*: `pass.coversZone(Zone::Airport)` returns `true` $\to$ `Rs 0.00` charged; stored balance remains untouched.

## C. Adaptation / Revised Design (2 Marks)
- **`TariffEngine`**: Uses `BASE_PAISE[4]` array indexing ($O(1)$) and mutually exclusive `isWeekend` vs. `isPeakHour(hour)` branching.
- **`MonthlyPass`**: Encapsulates `active`, `allowedZone1`, and `allowedZone2` with `coversZone(Zone)`.
- **`SmartCard`**: Composes `MonthlyPass`; `processJourney()` checks `pass.coversZone(z)` first, falling back to `TariffEngine::calculateFarePaise(...)` and the `MIN_RESIDUAL_PAISE` (`5000`) guard only for uncovered zones.

## D. Evidence-Based Defence (2 Marks)
- **Test Verification**:
  - `NM-8001` (`Rs 150.00`): Weekday peak Airport (`Rs 72.00`) leaves `Rs 78.00` (Approved); Weekend peak Airport (`Rs 54.00`) would leave `Rs 24.00 < Rs 50.00` (Denied); Weekend peak Outer (`Rs 27.00`) leaves `Rs 51.00 >= Rs 50.00` (Approved).
  - `NM-9002` (`Rs 60.00` + Pass for `Inner`/`Airport`): Airport and Inner trips charge `Rs 0.00`; uncovered Outer trip (`Rs 30.00`) is blocked because `60 - 30 = 30 < 50`.
- **Complexity & Trade-Offs**: Per-journey time remains **$O(1)$**, memory per card increases by only **12 bytes** (`bool` + two `Zone` enums for `MonthlyPass`), and existing `SmartCard` balance invariants remain intact without a full rewrite.
