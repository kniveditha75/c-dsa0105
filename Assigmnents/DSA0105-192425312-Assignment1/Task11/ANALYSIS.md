# Task 11 – Recommend and Defend the Final Design (4 Marks)

## 1. Recommended Types, Constants, and Classes
- **Types**: `long long` for all monetary amounts (in paise) and network-wide journey/revenue accumulators; `int` for hours (`0..23`) and percentages; `enum class Zone` and `enum class PassengerCategory` for discrete domains.
- **Constants**: `constexpr` values grouped inside a `TariffConfig` struct (`BASE_FARE_PAISE`, `PEAK_SURCHARGE_PCT`, `CONCESSION_PCT`, `MIN_RESIDUAL_PAISE`) validated via `static_assert`.
- **Classes**: `SmartCard` (encapsulating `balancePaise_` privately with atomic `tapExit()`), `TariffConfig` (stateless fare calculation), and `Journey` (audit logging).

## 2. Carrying Out a Fare Revision
- All tariff parameters live in one `TariffConfig` header/struct. Updating a zone fare, peak surcharge percentage, or minimum residual balance requires changing **one `constexpr` value**, running the automated test suite (`Task 9`), and deploying the verified binary.

## 3. Limitations & Network-Wide Correctness
- **Limitations**: Compile-time `constexpr` tables require a firmware rebuild/deploy when tariffs change, and a single-node in-memory `SmartCard` does not yet handle distributed multi-gate concurrency or offline card sync.
- **Network Correctness**: Verified across `20,000`, `500,000`, and `3,000,000` journeys/day—zero rounding error and zero overflow (`LLONG_MAX` accommodates >850 million days of peak network revenue).

## 4. Alternative Concept & Complexity Analysis
- **Alternative**: Loading the fare table from an external configuration file (`fares.cfg`) at gate startup instead of compiling it with `constexpr`.
- **Time & Space Complexity**: Reading $z$ zone fares at startup adds **$O(z)$ startup I/O time** (milliseconds) and **$O(z)$ heap/array space** ($8z$ bytes), while per-journey lookup remains **$O(1)$**.
- **Trade-Off**: File-based config avoids recompilation during tariff revisions, whereas `constexpr` eliminates file-parsing failure modes (missing/corrupted config file at a station gate) and enables compile-time `static_assert` verification.
