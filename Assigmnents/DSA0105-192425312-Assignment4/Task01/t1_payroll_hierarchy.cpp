#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

// Task 1: Diagnose and Repair Duplicated Classes (Payroll Hierarchy)

class Staff {
protected:
    std::string name;
    int id;

public:
    Staff(const std::string& n, int i) : name(n), id(i) {}
    virtual ~Staff() = default;
    virtual double pay() const = 0;
    virtual void print() const = 0;
};

class Professor : public Staff {
    double basic;
    double research;
    static constexpr double DA_RATE = 0.42; // named constant instead of magic number 0.42

public:
    Professor(const std::string& n, int i, double b, double r)
        : Staff(n, i), basic(b), research(r) {}

    double pay() const override {
        return basic + (basic * DA_RATE) + research;
    }

    void print() const override {
        std::cout << "Professor   | ID: " << id << " | Name: " << name << " | Pay: Rs " << std::fixed << std::setprecision(2) << pay() << '\n';
    }
};

class LabAssistant : public Staff {
    double basic;
    static constexpr double DA_RATE = 0.42;

public:
    LabAssistant(const std::string& n, int i, double b)
        : Staff(n, i), basic(b) {}

    double pay() const override {
        return basic + (basic * DA_RATE);
    }

    void print() const override {
        std::cout << "LabAsst     | ID: " << id << " | Name: " << name << " | Pay: Rs " << std::fixed << std::setprecision(2) << pay() << '\n';
    }
};

class GuestFaculty : public Staff {
    double hours;
    double rate;

public:
    GuestFaculty(const std::string& n, int code, double h, double r)
        : Staff(n, code), hours(h), rate(r) {}

    double pay() const override {
        return hours * rate;
    }

    void print() const override {
        std::cout << "GuestFaculty| ID: " << id << " | Name: " << name << " | Pay: Rs " << std::fixed << std::setprecision(2) << pay() << '\n';
    }
};

int main() {
    std::cout << "=== TASK 1: REPAIRED PAYROLL HIERARCHY ===\n";
    std::vector<std::unique_ptr<Staff>> payroll;
    payroll.push_back(std::make_unique<Professor>("Dr. Smith", 101, 50000.0, 15000.0));
    payroll.push_back(std::make_unique<LabAssistant>("Alice Brown", 201, 30000.0));
    payroll.push_back(std::make_unique<GuestFaculty>("Bob Martin", 301, 40.0, 1200.0));

    double totalPayroll = 0;
    for (const auto& member : payroll) {
        member->print();
        totalPayroll += member->pay();
    }
    std::cout << "----------------------------------------\n";
    std::cout << "Total Monthly Payroll: Rs " << std::fixed << std::setprecision(2) << totalPayroll << '\n';
    return 0;
}
