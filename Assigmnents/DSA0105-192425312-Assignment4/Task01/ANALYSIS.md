# Task 1 – Class Design Review (6 Marks)

## 1. Task 1.1 – Diagnose the Design
- **Repeated Fields & Rules**: `name`, `id`, `basic`, and `da` are duplicated across multiple classes with identical DA calculation rules (`basic * 0.42`).
- **Public Data Members**: All fields are `public`, violating encapsulation and object invariants.
- **Inconsistent Naming**: `name` vs `nm`, `id` vs `code`.
- **Unused Fields**: `da` is declared in `GuestFaculty` but never used in its calculation (`hours * rate`).
- **Magic Number**: `0.42` is hardcoded across classes instead of a named constant.
- **Extensibility**: Adding a new staff category requires writing an entirely independent class with duplicate fields, whereas inheritance allows clean extension.
- **Polymorphic Processing**: Without a common base class, storing different staff objects in a single `std::vector<Staff*>` loop is impossible.

## 2. Task 1.2 – Repair the Design & UML Hierarchy
- Introduced abstract base class `Staff` with protected fields (`name`, `id`) and pure virtual functions `pay()` and `print()`. `Professor`, `LabAssistant`, and `GuestFaculty` inherit publicly from `Staff`.

## 3. Task 1.3 – Design Defence
- **Defending the Hierarchy**: Inheritance centralizes common identity attributes (`name`, `id`) and enforces a uniform polymorphic interface (`pay()`, `print()`). Adding a new staff category (e.g., `AdministrativeStaff`) requires only creating a new derived class overriding `pay()`, without modifying existing payroll processing loops.
