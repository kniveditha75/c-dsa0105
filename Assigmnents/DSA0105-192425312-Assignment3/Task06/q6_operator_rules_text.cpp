#include <iostream>
#include <cstring>

// Q6: The Rules of Operator Overloading (A Simple Text Class for an SMS Gateway)

class Text {
    size_t len;
    char* buf;

public:
    Text(const char* s = "") : len(std::strlen(s)), buf(new char[len + 1]) {
        std::memcpy(buf, s, len + 1);
    }

    Text(const Text& o) : len(o.len), buf(new char[o.len + 1]) {
        std::memcpy(buf, o.buf, len + 1);
    }

    Text& operator=(const Text& o) {
        if (this == &o) return *this; // Self-assignment protection
        char* newBuf = new char[o.len + 1];
        std::memcpy(newBuf, o.buf, o.len + 1);
        delete[] buf;
        len = o.len;
        buf = newBuf;
        return *this;
    }

    ~Text() { delete[] buf; }

    Text operator+(const Text& rhs) const {
        Text res;
        delete[] res.buf;
        res.len = len + rhs.len;
        res.buf = new char[res.len + 1];
        std::memcpy(res.buf, buf, len);
        std::memcpy(res.buf + len, rhs.buf, rhs.len + 1);
        return res;
    }

    bool operator==(const Text& rhs) const { return std::strcmp(buf, rhs.buf) == 0; }
    bool operator!=(const Text& rhs) const { return !(*this == rhs); }

    friend std::ostream& operator<<(std::ostream& os, const Text& t) {
        return os << t.buf;
    }
};

int main() {
    std::cout << "=== Q6: SMS GATEWAY TEXT CLASS & OPERATOR RULES ===\n";
    Text a("Hello, "), b("SMS "), c("Gateway!");
    Text msg = a + b + c;
    msg = msg; // Self-assignment test
    std::cout << "Concatenated SMS: " << msg << '\n';
    std::cout << "Equality check  : " << std::boolalpha << (msg == Text("Hello, SMS Gateway!")) << '\n';
    return 0;
}
