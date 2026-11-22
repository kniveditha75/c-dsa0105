#include <iostream>
#include <string>

// Task 3: Constructors in Derived Classes and Member Classes

struct Engine {
    Engine() { std::cout << "Engine "; }
    ~Engine() { std::cout << "~Engine "; }
};

struct Vehicle {
    Vehicle() { std::cout << "Vehicle "; }
    ~Vehicle() { std::cout << "~Vehicle "; }
};

struct Car : Vehicle {
    Engine e;
    Car() { std::cout << "Car "; }
    ~Car() { std::cout << "~Car "; }
};

class Person {
protected:
    std::string name;
    int age;
public:
    Person(const std::string& n, int a) : name(n), age(a) {}
};

class Address {
    std::string city;
    int pin;
public:
    Address(const std::string& c, int p) : city(c), pin(p) {}
    std::string str() const { return city + "-" + std::to_string(pin); }
};

class Student : public Person {
    long long regNo;
    Address home;

public:
    // TODO 1: Initialise Person base, regNo, and home Address member in initializer list
    Student(const std::string& n, int a, long long r, const std::string& c, int p)
        : Person(n, a), regNo(r), home(c, p) {}

    void print() const {
        std::cout << regNo << ' ' << name << " (" << age << ") " << home.str() << '\n';
    }
};

int main() {
    std::cout << "=== TASK 3: PREDICT THE OUTPUT (VEHICLE / CAR) ===\n";
    {
        Car c;
        std::cout << "| ";
    }
    std::cout << '\n';

    std::cout << "\n=== TASK 3: COMPLETE THE CODE VERIFICATION ===\n";
    Student s("Kavya", 19, 192311001, "Salem", 636001);
    s.print();
    return 0;
}
