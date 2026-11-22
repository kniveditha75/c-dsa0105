#include <iostream>
#include <vector>

// Task 4: Pointers to Derived Classes: Forensics

struct Account {
    double rate() const { return 3.5; }
    virtual double vrate() const { return 3.5; }
    virtual ~Account() = default;
};

struct SeniorAccount : Account {
    double* history = new double[100];
    double rate() const { return 4.0; }
    double vrate() const override { return 4.0; }
    ~SeniorAccount() { delete[] history; }
};

int main() {
    std::cout << "=== TASK 4: PREDICT THE OUTPUT SNIPPET ===\n";
    SeniorAccount s;
    Account* p = &s;
    Account copy = s; // Object slicing!
    std::cout << p->rate() << ' ' << p->vrate() << ' ' << copy.vrate() << '\n';

    std::cout << "\n=== TASK 4: REPAIRED POLYMORPHIC ACCOUNTS ===\n";
    Account* accounts[2] = { new Account, new SeniorAccount };
    for (Account* a : accounts) {
        std::cout << "Rate: " << a->vrate() << "%\n";
    }
    for (Account* a : accounts) {
        delete a; // Safe polymorphic destruction due to virtual destructor
    }
    return 0;
}
