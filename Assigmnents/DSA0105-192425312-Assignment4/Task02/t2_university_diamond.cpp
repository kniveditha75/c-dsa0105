#include <iostream>
#include <string>

// Task 2: University People Management & Diamond Inheritance

struct Person {
    std::string name;
    int id;
    std::string phone;
    Person() { std::cout << "Person "; }
    virtual ~Person() = default;
};

struct Student : virtual Person {
    std::string programme;
    double cgpa;
    Student() { std::cout << "Student "; }
};

struct Staff : virtual Person {
    std::string department;
    double salary;
    Staff() { std::cout << "Staff "; }
};

struct TeachingAssistant : Student, Staff {
    TeachingAssistant() { std::cout << "TA "; }
};

int main() {
    std::cout << "=== TASK 2: PREDICT THE OUTPUT SNIPPET ===\n";
    TeachingAssistant ta;
    std::cout << '\n';

    // Verify virtual inheritance ensures single Person instance subobject
    std::cout << "sizeof(TeachingAssistant) with virtual base: " << sizeof(TeachingAssistant) << " bytes\n";
    return 0;
}
