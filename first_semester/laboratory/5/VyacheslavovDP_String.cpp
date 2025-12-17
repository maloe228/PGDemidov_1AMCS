#include "VyacheslavovDP_String.h"
#include <algorithm>

using namespace std;

VyacheslavovDP_String::VyacheslavovDP_String() {
    str = new char[1];
    str[0] = '\0';
    size = 0;
}

VyacheslavovDP_String::VyacheslavovDP_String(const char* s) {
    if (s == nullptr) {
        size = 0;
        str = new char[1];
        str[0] = '\0';
    } else {
        size_t len = 0;
        const char* c = s;
        while (*c != '\0') {
            len++;
            c++;
        }
        this->size = len;
        str = new char[size + 1];
        copy(s, s + size, str);
        str[size] = '\0';
    }
}

VyacheslavovDP_String::VyacheslavovDP_String(const VyacheslavovDP_String& s) {
    size = s.size;
    str = new char[size + 1];
    copy(s.str, s.str + size, str);
    str[size] = '\0';
}

VyacheslavovDP_String::~VyacheslavovDP_String() {
    delete[] str;
}

size_t VyacheslavovDP_String::length() const {
    return size;
}

char& VyacheslavovDP_String::operator[](size_t index) {
    if (index >= size) {
        throw "Index out of range";
    }
    return str[index];
}

const char& VyacheslavovDP_String::operator[](size_t index) const {
    if (index >= size) {
        throw "Index out of range";
    }
    return str[index];
}

void VyacheslavovDP_String::append(const VyacheslavovDP_String& s) {
    size_t newLen = size + s.size;
    char* newStr = new char[newLen + 1];
    copy(str, str + size, newStr);
    copy(s.str, s.str + s.size, newStr + size);
    newStr[newLen] = '\0';
    delete[] str;
    str = newStr;
    size = newLen;
}

VyacheslavovDP_String VyacheslavovDP_String::substr(size_t start, size_t count) const {
    if (start >= size) {
        throw "Start position out of range";
    }
    size_t actual_len = min(count, size - start);
    char* new_str = new char[actual_len + 1];
    copy(str + start, str + start + actual_len, new_str);
    new_str[actual_len] = '\0';
    VyacheslavovDP_String result(new_str);
    delete[] new_str;
    return result;
}

VyacheslavovDP_String& VyacheslavovDP_String::operator=(const VyacheslavovDP_String& s) {
    if (this != &s) {
        delete[] str;
        size = s.size;
        str = new char[size + 1];
        copy(s.str, s.str + size, str);
        str[size] = '\0';
    }
    return *this;
}

VyacheslavovDP_String VyacheslavovDP_String::operator+(const VyacheslavovDP_String& s) const {
    VyacheslavovDP_String res;
    delete[] res.str;
    res.size = size + s.size;
    res.str = new char[res.size + 1];
    copy(str, str + size, res.str);
    copy(s.str, s.str + s.size, res.str + size);
    res.str[res.size] = '\0';
    return res;
}

bool VyacheslavovDP_String::operator==(const VyacheslavovDP_String& s) const {
    if (size != s.size) return false;
    for (size_t i = 0; i < size; i++) {
        if (str[i] != s.str[i]) return false;
    }
    return true;
}

bool VyacheslavovDP_String::operator!=(const VyacheslavovDP_String& s) const {
    return !(*this == s);
}

bool VyacheslavovDP_String::operator<(const VyacheslavovDP_String& s) const {
    size_t min_len = min(size, s.size);
    for (size_t i = 0; i < min_len; i++) {
        if (str[i] != s.str[i]) {
            return str[i] < s.str[i];
        }
    }
    return size < s.size;
}

bool VyacheslavovDP_String::operator>(const VyacheslavovDP_String& s) const { return s < *this; }
bool VyacheslavovDP_String::operator<=(const VyacheslavovDP_String& s) const { return !(s < *this); }
bool VyacheslavovDP_String::operator>=(const VyacheslavovDP_String& s) const { return !(*this < s); }

std::ostream& operator<<(std::ostream& out, const VyacheslavovDP_String& s) {
    for (size_t i = 0; i < s.size; i++) {
        out << s.str[i];
    }
    return out;
}

std::istream& operator>>(std::istream& in, VyacheslavovDP_String& s) {
    char buffer[1024];
    in >> buffer;
    delete[] s.str;
    s.size = 0;
    while (buffer[s.size] != '\0') s.size++;
    s.str = new char[s.size + 1];
    copy(buffer, buffer + s.size, s.str);
    s.str[s.size] = '\0';
    return in;
}
