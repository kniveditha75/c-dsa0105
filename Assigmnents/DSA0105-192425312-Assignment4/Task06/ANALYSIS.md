# Task 6 – Design Challenge: Vehicle Rental Fleet (13 Marks)

## 1. Stage 1 to 3 – Problem Interpretation & Hierarchy Design
- **Entities**: `Vehicle` (abstract base), `MotorVehicle`, `Car`, `ElectricCar`, and extensible `ElectricBus`.
- **Polymorphic Behaviour**: `computeCharge()` computes rates differently (e.g., kWh charging for EVs vs daily rates for ICE cars).
- **Storage**: Fleet stored as `std::vector<std::unique_ptr<Vehicle>>`, enabling polymorphic dispatch.

## 2. Stage 4 & 5 – Implementation & Extension Demonstration
- Successfully demonstrated renting, returning with late penalties, and adding `ElectricBus` seamlessly without altering base class interfaces.
