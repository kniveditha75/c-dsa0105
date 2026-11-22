# Task 8 – Read and Print Data Safely (4 Marks)

## 1. Handling Invalid Input with `std::cin`
- When the gate operator enters letters (e.g., `"abc"`) instead of an integer:
  1. `std::cin >> value` fails and sets `std::ios::failbit` (`std::cin.fail() == true`), leaving the offending characters unread in the stream buffer.
  2. `std::cin.clear()` resets the error flags back to `goodbit`.
  3. `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')` flushes the rest of the invalid line up to the newline delimiter so the next prompt starts cleanly.

## 2. Formatting Money with `<iomanip>`
- `std::setw(2) << std::setfill('0') << (paise % 100)` guarantees two-digit paise formatting (`Rs 10.05` instead of `Rs 10.5`), followed by `std::setfill(' ')` to reset the fill character so subsequent columns pad with spaces.

## 3. Alternative Concept & Complexity Analysis
- **Alternative**: Reading whole lines with `std::getline(std::cin, line)` and parsing with `std::stoi(line)` inside a `try { ... } catch (const std::exception&)` block.
- **Time Complexity**: **$O(L)$** per input line of length $L$ in both approaches (scanning $L$ characters).
- **Space Complexity**: `std::getline` allocates a `std::string` buffer of **$O(L)$ heap/SSO space** per line, whereas `cin >> value` uses **$O(1)$ fixed stack space** (4 bytes for `int` + existing `streambuf`).
- **Error Recovery**: `std::getline` + `std::stoi` always consumes the entire line cleanly (preventing trailing-garbage bugs like `"12abc"` silently parsing as `12` in `cin >>`), at the cost of exception-handling overhead on bad input.
