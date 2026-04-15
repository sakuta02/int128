#pragma once

#include <algorithm>
#include <cstdint>
#include <iosfwd>
#include <string>
#include <string_view>

class Int128 {
public:
    Int128();
    Int128(int64_t value);
    Int128(std::string_view str);

    explicit operator int64_t() const;
    explicit operator double() const;

    std::string str() const;

    Int128 operator+() const;
    Int128 operator-() const;

    Int128& operator+=(const Int128& other);
    Int128& operator-=(const Int128& other);
    Int128& operator*=(const Int128& other);
    Int128& operator/=(const Int128& other);

    friend Int128 operator+(Int128 left, const Int128& right);
    friend Int128 operator-(Int128 left, const Int128& right);
    friend Int128 operator*(Int128 left, const Int128& right);
    friend Int128 operator/(Int128 left, const Int128& right);

    friend bool operator==(const Int128& left, const Int128& right);
    friend bool operator!=(const Int128& left, const Int128& right);

    friend std::ostream& operator<<(std::ostream& out, const Int128& value);

private:
    __int128 value_;
};
