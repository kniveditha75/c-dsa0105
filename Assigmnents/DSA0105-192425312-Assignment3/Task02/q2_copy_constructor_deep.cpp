#include <iostream>
#include <string>

// Q2: Copy Constructors: Shallow and Deep Copies (Hospital Prescription Records)

class Prescription {
    int n;
    std::string* medicines; // dynamically allocated array

public:
    explicit Prescription(int count) : n(count), medicines(new std::string[count]) {}

    // TODO 1: Copy constructor: allocate a NEW array of the same size and copy every medicine (deep copy)
    Prescription(const Prescription& other) : n(other.n), medicines(new std::string[other.n]) {
        for (int i = 0; i < n; ++i) {
            medicines[i] = other.medicines[i];
        }
    }

    // TODO 2: Copy assignment: guard against self-assignment, build a new array, copy, release old and return *this
    Prescription& operator=(const Prescription& other) {
        if (this == &other) return *this; // self-assignment guard
        std::string* newArr = new std::string[other.n];
        for (int i = 0; i < other.n; ++i) {
            newArr[i] = other.medicines[i];
        }
        delete[] medicines;
        n = other.n;
        medicines = newArr;
        return *this;
    }

    ~Prescription() {
        // TODO 3: Release the dynamically allocated array
        delete[] medicines;
    }

    void set(int i, const std::string& m) { medicines[i] = m; }
    std::string get(int i) const { return medicines[i]; }
};

int main() {
    std::cout << "=== Q2: DEEP COPY & RULE OF THREE VERIFICATION ===\n";
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p; // copy constructor
    q.set(1, "Cetirizine");

    Prescription r(1);
    r = p;              // copy assignment
    p.set(0, "Ibuprofen");

    // Self-assignment test
    r = r;

    std::cout << p.get(0) << ' ' << p.get(1) << " | "
              << q.get(0) << ' ' << q.get(1) << " | "
              << r.get(0) << ' ' << r.get(1) << '\n';
    return 0;
}
