# Task B1 – Implement and Validate Polymorphic Billing (7 Marks)

## 1. Experimental Investigation & Verification
- **Test Execution**: Tested `OutPatient` (`Ravi`, Rs 500 consultation + Rs 1200 tests = Rs 1700) and `InPatient` (`Meena`, 3 days @ Rs 2500/day + Rs 40000 surgery = Rs 47500). Total: Rs 49,200.
- **Runtime Binding Proof**: Removing `virtual` from `total()` causes base pointer calls to invoke `Bill::total()` (or fails to compile if pure virtual), breaking polymorphic dispatch.
- **Virtual Destructor Proof**: Removing `virtual` from `~Bill()` when deleting derived objects through `Bill*` causes undefined behaviour and memory leaks for derived resources.
