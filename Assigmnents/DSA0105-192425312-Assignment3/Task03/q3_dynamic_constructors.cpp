#include <iostream>
#include <string>

// Q3: Dynamic Constructors and Destructors (Auditorium Seat Booking)

struct Logger {
    std::string n;
    Logger(const std::string& s) : n(s) { std::cout << '+' << n << ' '; }
    Logger(const Logger& o) : n(o.n + "c") { std::cout << "copy" << n << ' '; }
    ~Logger() { std::cout << '-' << n << ' '; }
};

void use(Logger) { std::cout << "use "; }

class Auditorium {
    int rows, cols;
    char** seats;

public:
    Auditorium(int r, int c) : rows(r), cols(c), seats(nullptr) {
        if (rows > 0 && cols > 0) {
            seats = new char*[rows];
            for (int i = 0; i < rows; ++i) {
                seats[i] = new char[cols];
                for (int j = 0; j < cols; ++j) seats[i][j] = 'O'; // Open
            }
        }
        std::cout << "[Constructed " << rows << "x" << cols << " Auditorium]\n";
    }

    ~Auditorium() {
        int booked = 0;
        if (seats) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (seats[i][j] == 'X') booked++;
                }
                delete[] seats[i];
            }
            delete[] seats;
        }
        std::cout << "[Destroyed Auditorium | Final Booked Seats: " << booked << "]\n";
    }

    void book(int r, int c) {
        if (seats && r >= 0 && r < rows && c >= 0 && c < cols) seats[r][c] = 'X';
    }
};

int main() {
    std::cout << "=== Q3: PREDICT THE OUTPUT (LOGGER) ===\n";
    Logger a("A");
    {
        Logger b("B");
    }
    use(a);
    Logger* p = new Logger("P");
    delete p;
    std::cout << "end \n";

    std::cout << "\n=== Q3: DYNAMIC AUDITORIUM SEAT MAP (RAII) ===\n";
    Auditorium hall(10, 20);
    hall.book(0, 0);
    hall.book(2, 5);
    Auditorium emptyHall(0, 0); // Edge case: zero rows
    return 0;
}
