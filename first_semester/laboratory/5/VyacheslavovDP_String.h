#pragma once
#include <iostream>
#include <algorithm>

class VyacheslavovDP_String {
private:
    char* str = nullptr;
    size_t size = 0;

public:
    VyacheslavovDP_String();
    VyacheslavovDP_String(const char* s);
    VyacheslavovDP_String(const VyacheslavovDP_String& s);
    ~VyacheslavovDP_String();

    size_t length() const;
    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    void append(const VyacheslavovDP_String& s);

    VyacheslavovDP_String substr(size_t start, size_t count) const;

    VyacheslavovDP_String& operator=(const VyacheslavovDP_String& s);
    VyacheslavovDP_String operator+(const VyacheslavovDP_String& s) const;

    bool operator==(const VyacheslavovDP_String& s) const;
    bool operator!=(const VyacheslavovDP_String& s) const;
    bool operator<(const VyacheslavovDP_String& s) const;
    bool operator>(const VyacheslavovDP_String& s) const;
    bool operator<=(const VyacheslavovDP_String& s) const;
    bool operator>=(const VyacheslavovDP_String& s) const;

    friend std::ostream& operator<<(std::ostream& out, const VyacheslavovDP_String& s);
    friend std::istream& operator>>(std::istream& in, VyacheslavovDP_String& s);
};
