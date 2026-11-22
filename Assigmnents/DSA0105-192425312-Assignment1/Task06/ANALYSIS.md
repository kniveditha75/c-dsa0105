# Task 6 – Design the Control Structures (4 Marks)

## 1. SIMATS Engineering Standard Pseudocode — `ComputeMetroFare`
```text
ALGORITHM ComputeMetroFare(zone, hour, balance)
INPUT:
    zone    : Zone enumeration (Inner, Middle, Outer)
    hour    : Integer representing hour of day (0..23)
    balance : Long integer representing card balance in paise
OUTPUT:
    updatedBalance : Long integer balance after journey (or unchanged if denied)

CONSTANTS:
    BASE_INNER <- 1000, BASE_MIDDLE <- 2000, BASE_OUTER <- 3000
    SURCHARGE_PCT <- 20
    MIN_BALANCE <- 5000

BEGIN
    IF hour < 0 OR hour > 23 THEN
        PRINT "Invalid hour"
        RETURN balance
    ENDIF

    SWITCH (zone)
        CASE Inner:
            baseFare <- BASE_INNER
        CASE Middle:
            baseFare <- BASE_MIDDLE
        CASE Outer:
            baseFare <- BASE_OUTER
        DEFAULT:
            PRINT "Unknown zone"
            RETURN balance
    ENDSWITCH

    IF (hour >= 8 AND hour < 10) OR (hour >= 17 AND hour < 20) THEN
        finalFare <- baseFare + (baseFare * SURCHARGE_PCT) DIV 100
    ELSE
        finalFare <- baseFare
    ENDIF

    IF (balance - finalFare) >= MIN_BALANCE THEN
        balance <- balance - finalFare
        PRINT "Approved: Fare =", finalFare, "Balance =", balance
    ELSE
        PRINT "Denied: Insufficient balance"
    ENDIF

    RETURN balance
END
```

## 2. Control Structure Choices
- **`switch` vs. `if-else` vs. `?:`**: `switch` is ideal for multi-way dispatch on discrete `enum class Zone` constants; `if-else` handles multi-statement approval/denial branches; `?:` is best for concise inline value selection.
- **Loop Comparison**:
  - **Range-based `for` (`for (const Trip& t : trips)`)**: Best for iterating through a fixed batch of trips without index-out-of-bounds risk.
  - **Index `for`**: Needed only when the trip index itself is logged.
  - **`while`**: Best for continuous gate polling until an exit sentinel or card-depleted condition.
- **`break` and `continue`**: `break` prevents fall-through between `switch` cases; `continue` skips malformed/invalid journey records in a batch without aborting the entire day's processing.
- **Unmatched `switch` Case**: If no `case` matches and no `default:` label exists, control skips the entire `switch` block silently. Including `default:` ensures unknown zones are caught safely.

## 3. Alternative Concept & Complexity Analysis
- **Alternative**: Direct array lookup `constexpr long long FARE[] = {1000, 2000, 3000}; base = FARE[static_cast<int>(z)];` instead of a `switch`.
- **Time Complexity**: **$O(1)$** in both (compilers optimize dense `switch` statements into a jump table, matching array indexing).
- **Space Complexity**: The `FARE` array uses $3 \times 8 = 24$ bytes ($O(1)$); a `switch` jump table uses ~24 bytes in `.rodata`.
- **Adaptability to a 4th Zone**: With an array (`FARE[static_cast<int>(z)]`), adding `Zone::Airport` requires only adding `6000` to the array initializer. With a `switch`, every `switch (z)` across the codebase must be edited to add `case Zone::Airport:`.
