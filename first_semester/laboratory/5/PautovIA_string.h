#pragma once
#include <iostream>
#include <algorithm>

class PautovIA_string {
private:
    char* str = nullptr;
    size_t size = 0;

public:
    PautovIA_string();
    PautovIA_string(const char* s);
    PautovIA_string(const PautovIA_string& s);
    ~PautovIA_string();

    size_t length() const;
    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    void append(const PautovIA_string& s);

    PautovIA_string substr(size_t start, size_t count) const;

    PautovIA_string& operator=(const PautovIA_string& s);
    PautovIA_string operator+(const PautovIA_string& s) const;

    bool operator==(const PautovIA_string& s) const;
    bool operator!=(const PautovIA_string& s) const;
    bool operator<(const PautovIA_string& s) const;
    bool operator>(const PautovIA_string& s) const;
    bool operator<=(const PautovIA_string& s) const;
    bool operator>=(const PautovIA_string& s) const;

    friend std::ostream& operator<<(std::ostream& out, const PautovIA_string& s);
    friend std::istream& operator>>(std::istream& in, PautovIA_string& s);
};