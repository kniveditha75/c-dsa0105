# DSA01-<RegisterNumber>-Assignment1

## Object Oriented Programming with C++ — Assignment 1 (CO1)

**Assignment Title:** Design, Implement and Validate the Fare Logic of a City Metro Smart-Card System  
**Student Name:** Cheerala Jyothi  
**Register Number:** `192425312`  
**Compiler \& Version:** `g++ (Debian 12.2.0) 12.2.0` (compatible with `g++ 13+`)  
**Compilation Command:** `g++ -std=c++17 -Wall -Wextra <source\_file>.cpp -o <executable>`

\---

## Repository Structure

* `Task01/` — Object-Oriented Domain Analysis (`task01\_oop\_analysis.cpp`, `input.txt`, `output.txt`, `Task01\_output\_screenshot.png`, `ANALYSIS.md`)
* `Task02/` — Tokens, Keywords, Identifiers \& `constexpr` / `enum class` (`task02\_tokens\_constants.cpp`, ...)
* `Task03/` — Data Types, `<climits>` Ranges \& Precision Drift (`task03\_data\_types.cpp`, ...)
* `Task04/` — Implicit Conversions \& Predict the Output (`task04\_implicit\_conversions.cpp`, ...)
* `Task05/` — Operator Precedence, Associativity \& Predict the Output (`task05\_precedence\_expressions.cpp`, ...)
* `Task06/` — Control Structures, SIMATS Pseudocode \& Complete the Code (`task06\_control\_structures.cpp`, ...)
* `Task07/` — Procedural vs. Object-Oriented `SmartCard` (`task07\_procedural\_vs\_oop.cpp`, ...)
* `Task08/` — Safe Gate I/O (`cin.fail`, `cin.clear`, `cin.ignore`) \& `<iomanip>` (`task08\_safe\_io.cpp`, ...)
* `Task09/` — Complete Fare Logic \& Automated Boundary/Invalid Test Suite (`task09\_test\_suite.cpp`, ...)
* `Task10/` — Scaling Comparison (`20,000`, `500,000`, `3,000,000` Journeys) (`task10\_expectation\_vs\_execution.cpp`, ...)
* `Task11/` — Recommended Final Production Design (`task11\_final\_recommendation.cpp`, ...)
* `Task12/` — Day-4 Design Challenge (Airport Zone, Weekend Discount, 2-Zone Monthly Pass) (`task12\_design\_challenge.cpp`, ...)
* `Assignment1\_Report.docx` — Complete formatted report covering Tasks 1–12 with UML diagram, SIMATS pseudocode, test tables, and Big-O complexity analyses.

\---

## Steps to Compile and Run Each Program

```bash
# Example for Task 01:
cd Task01
g++ -std=c++17 -Wall -Wextra task01\_oop\_analysis.cpp -o task01
./task01

# Task 08 uses sample invalid+valid input redirection:
cd ../Task08
g++ -std=c++17 -Wall -Wextra task08\_safe\_io.cpp -o task08
./task08 < input.txt
```

\---

## Short Note on the Result of Each Task

1. **Task 01:** Encapsulated `SmartCard`, `FareTable`, `Journey`, and `Zone`; verified Rs 50 minimum post-journey balance and concession rules.
2. **Task 02:** Replaced scattered magic numbers with compile-time `constexpr` constants and `enum class Zone`, verified via `static\_assert`.
3. **Task 03:** Demonstrated that 32-bit `int` overflows at 3,000,000 journeys (`10.8B` paise > `INT\_MAX`) and `double` drifts, confirming `long long` paise.
4. **Task 04:** Verified predicted output (`3 3.5`, `C 68`, `1 true`, `s >= u`) and demonstrated `static\_cast` + brace initialization safety.
5. **Task 05:** Verified predicted output (`11 16`, `9 6 4`, `6 4`, `3 1 -3 -1`, `18`) and operator precedence for peak/surcharge/concession logic.
6. **Task 06:** Completed `fare()` and `canTravel()` TODOs matching expected output (`Rs 10.00`, `Rs 36.00`, `Denied`), plus 10:00 AM and 8:00 PM off-peak boundary checks.
7. **Task 07:** Compared free-function procedural style against encapsulated `SmartCard`, proving private balance prevents negative balances.
8. **Task 08:** Recovered cleanly from non-numeric inputs (`abc`, `xyz`) using `cin.clear()` and `cin.ignore()`, printing aligned `<iomanip>` tables.
9. **Task 09:** Passed all 12 automated normal, boundary (`08:00`, `10:00`, `17:00`, `20:00`, exact Rs 50 residual), and invalid tests plus the 5-trip hand-calculated batch (`Rs 108.50`).
10. **Task 10:** Measured exact totals vs. `double` drift and 32-bit `int` overflow across `20,000`, `500,000`, and `3,000,000` journeys.
11. **Task 11:** Recommended `namespace NammaMetro` with `constexpr` tariff tables and `long long` paise `SmartCard` for zero-drift network-wide deployment.
12. **Task 12:** Modified the design to support Zone 4 (`Airport` Rs 60), non-stacking 10% weekend discount, and a 2-zone `MonthlyPass` class.

