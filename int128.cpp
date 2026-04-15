#include "int128.h"

#include <algorithm>
#include <iostream>

Int128::Int128() : value_(0) {}

Int128::Int128(int64_t value) : value_(value) {}

Int128::Int128(std::string_view str) : value_(0) {
    bool negative = false;
    std::size_t pos = 0;

    if (!str.empty() && str[0] == '-') {
        negative = true;
        pos = 1;
    } else if (!str.empty() && str[0] == '+') {
        pos = 1;
    }

    for (; pos < str.size(); ++pos) {
        char c = str[pos];
        if (c < '0' || c > '9') {
            continue;
        }
        if (negative) {
            value_ = value_ * 10 - (c - '0');
        } else {
            value_ = value_ * 10 + (c - '0');
        }
    }
}

Int128::operator int64_t() const {
    return static_cast<int64_t>(value_);
}

Int128::operator double() const {
    return static_cast<double>(value_);
}

std::string Int128::str() const {
    if (value_ == 0) {
        return "0";
    }

    bool negative = value_ < 0;
    unsigned __int128 number = negative
        ? static_cast<unsigned __int128>(-(value_ + 1)) + 1
        : static_cast<unsigned __int128>(value_);

    std::string result;
    while (number > 0) {
        int digit = static_cast<int>(number % 10);
        result.push_back(static_cast<char>('0' + digit));
        number /= 10;
    }

    if (negative) {
        result.push_back('-');
    }

    std::reverse(result.begin(), result.end());
    return result;
}

Int128 Int128::operator+() const {
    return *this;
}

Int128 Int128::operator-() const {
    Int128 result;
    result.value_ = -value_;
    return result;
}

Int128& Int128::operator+=(const Int128& other) {
    value_ += other.value_;
    return *this;
}

Int128& Int128::operator-=(const Int128& other) {
    value_ -= other.value_;
    return *this;
}

Int128& Int128::operator*=(const Int128& other) {
    value_ *= other.value_;
    return *this;
}

Int128& Int128::operator/=(const Int128& other) {
    value_ /= other.value_;
    return *this;
}

Int128 operator+(Int128 left, const Int128& right) {
    left += right;
    return left;
}

Int128 operator-(Int128 left, const Int128& right) {
    left -= right;
    return left;
}

Int128 operator*(Int128 left, const Int128& right) {
    left *= right;
    return left;
}

Int128 operator/(Int128 left, const Int128& right) {
    left /= right;
    return left;
}

bool operator==(const Int128& left, const Int128& right) {
    return left.value_ == right.value_;
}

bool operator!=(const Int128& left, const Int128& right) {
    return !(left == right);
}

std::ostream& operator<<(std::ostream& out, const Int128& value) {
    out << value.str();
    return out;
}
