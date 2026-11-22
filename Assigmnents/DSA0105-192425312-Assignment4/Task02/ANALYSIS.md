# Task 2 – From Requirement to Hierarchy (8 Marks)

## 1. Predict the Output Analysis
- **Output**: `Person Student Staff TA `
- **Explanation**: `TeachingAssistant` inherits from `Student` and `Staff`. Because both inherit `virtual Person`, the compiler constructs a **single shared `Person` subobject** first, followed by `Student`, `Staff`, and finally `TeachingAssistant`.
- **Without `virtual`**: Removing `virtual` causes the **diamond inheritance ambiguity problem**, where `TeachingAssistant` inherits two separate `Person` subobjects, resulting in duplicate fields and compiler ambiguity when accessing `name` or `id`.

## 2. Task 2.1 & 2.2 – Relationships & Diamond Resolution
- `Student` is-a `Person` (single inheritance).
- `Staff` is-a `Person` (single inheritance).
- `TeachingAssistant` is-a `Student` and is-a `Staff` (multiple inheritance).
- `ResearchScholar` is-a `Student` with a fellowship (has-a fellowship object).
- Virtual base classes (`virtual public Person`) ensure only one instance of the base class exists in the derived class.
