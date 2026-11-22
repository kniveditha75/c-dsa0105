#include <iostream>
#include <string>
#include <stdexcept>

// Q1: Constructors and Constructor Overloading (Library Book Records)

class Book {
private:
    std::string title;
    std::string author;
    int copies;

public:
    // 1. Default constructor delegating to full parameterised constructor
    Book() : Book("Untitled", "Unknown", 0) {}

    // 2. Overloaded constructor for donated book with only title (explicit prevents implicit string->Book conversion)
    explicit Book(const std::string& t) : Book(t, "Donated", 1) {}

    // 3. Full parameterised constructor using member initializer list
    Book(const std::string& t, const std::string& a, int c)
        : title(t), author(a), copies(c < 0 ? 0 : c) {
        if (c < 0) {
            std::cout << "[Warning] Negative copies (" << c << ") clamped to 0 for '" << title << "'\n";
        }
    }

    void print() const {
        std::cout << "Book: \"" << title << "\" by " << author << " | Copies: " << copies << '\n';
    }
};

int main() {
    std::cout << "=== Q1: CONSTRUCTORS & DELEGATION ===\n";
    Book b1;                                            // Default constructor
    Book b2("Clean Code");                              // Explicit single-arg constructor
    Book b3("The C++ Programming Language", "Bjarne", 5); // Full parameterised constructor
    Book b4("Invalid Stock Book", "Author X", -3);      // Negative copies test

    b1.print();
    b2.print();
    b3.print();
    b4.print();

    // Array of books relies on default constructor
    Book shelf[2];
    std::cout << "Shelf array initialized with default constructor (" << 2 << " slots).\n";
    return 0;
}
