#pragma once
#include <iostream>
#include <stdexcept>

class BitString {
private:
    unsigned char *_data;
    size_t _size;

public:
    BitString();
    BitString(const size_t &size, unsigned char t = '0');
    BitString(const std::string &t);
    BitString(const BitString &other);
    BitString(BitString &&other) noexcept;
    BitString &operator=(const BitString &other);
    BitString &operator=(BitString &&other);
    BitString(const std::initializer_list<unsigned char> &t);
    ~BitString();

    BitString &operator+=(const BitString &other);
    BitString operator+(const BitString &other) const;
    BitString &operator-=(const BitString &other);
    BitString operator-(const BitString &other) const;

    BitString operator&(const BitString &other) const;
    BitString operator|(const BitString &other) const;
    BitString operator^(const BitString &other) const;
    BitString operator~() const;

    bool operator<(const BitString &other) const;
    bool operator>(const BitString &other) const;
    bool operator==(const BitString &other) const;
    bool operator!=(const BitString &other) const;

    size_t getSize() const;
    unsigned char getBit(size_t index) const;
    void setBit(size_t index, unsigned char value);
    void shrink();
    friend std::ostream &operator<<(std::ostream &out, const BitString &b);

private:
    static unsigned char get_char(size_t i) { return '0' + i; }
    static int get_int(unsigned char i) { return i - '0'; }
};