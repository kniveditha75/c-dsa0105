#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// Q5: Overloading Increment, Comparison and Subscript Operators (Music Playlist & Track Timer)

struct Counter {
    int v;
    Counter& operator++() { ++v; return *this; }                    // prefix
    Counter operator++(int) { Counter old = *this; ++v; return old; } // postfix
};

class Time {
    int h, m, s;
    void normalize() {
        m += s / 60; s %= 60;
        h += m / 60; m %= 60;
        h %= 24;
    }
public:
    Time(int hh = 0, int mm = 0, int ss = 0) : h(hh), m(mm), s(ss) { normalize(); }

    Time& operator++() { ++s; normalize(); return *this; }
    Time operator++(int) { Time old = *this; ++(*this); return old; }

    bool operator==(const Time& o) const { return h == o.h && m == o.m && s == o.s; }
    bool operator<(const Time& o) const {
        return (h * 3600 + m * 60 + s) < (o.h * 3600 + o.m * 60 + o.s);
    }

    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        os << t.h << ':' << (t.m < 10 ? "0" : "") << t.m << ':' << (t.s < 10 ? "0" : "") << t.s;
        return os;
    }
};

class Playlist {
    std::vector<std::string> tracks;
public:
    Playlist(std::initializer_list<std::string> list) : tracks(list) {}

    std::string& operator[](int idx) {
        if (idx < 0 || idx >= static_cast<int>(tracks.size())) {
            throw std::out_of_range("Playlist index out of bounds");
        }
        return tracks[idx];
    }

    const std::string& operator[](int idx) const {
        if (idx < 0 || idx >= static_cast<int>(tracks.size())) {
            throw std::out_of_range("Playlist index out of bounds");
        }
        return tracks[idx];
    }
};

int main() {
    std::cout << "=== Q5: PREDICT THE OUTPUT (COUNTER) ===\n";
    Counter c{5};
    Counter a = c++;
    Counter b = ++c;
    std::cout << a.v << ' ' << b.v << ' ' << c.v << '\n';

    std::cout << "\n=== Q5: TIME ROLL-OVER & PLAYLIST SUBSCRIPT ===\n";
    Time t(0, 59, 59);
    std::cout << "Before ++t: " << t << " -> After ++t: " << ++t << '\n';

    Playlist pl{"Track 1", "Track 2"};
    std::cout << "pl[1] = " << pl[1] << '\n';
    try {
        std::cout << pl[2] << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "Caught expected bounds exception: " << e.what() << '\n';
    }
    return 0;
}
