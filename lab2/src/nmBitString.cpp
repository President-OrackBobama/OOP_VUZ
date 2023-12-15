#include "../include/nmBitString.hpp"

BitString::BitString() : _size(1) {
    _data = new unsigned char[_size];
    _data[0] = '0';
}

BitString::BitString(const size_t &StrSize, unsigned char t) {
    if (t != '0' && t != '1') {
        throw std::logic_error("Not 0-1 digit.");
    }
    if (t == '0') {
        _data = new unsigned char[1];
        _data[0] = '0';
        _size = 1;
    } else {
        _size = StrSize;
        _data = new unsigned char[_size];
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = t;
        }
    }
}

BitString::BitString(const std::string &t) { //траблы
    _data = new unsigned char[t.size()];
    for (size_t i = 0; i < t.size(); ++i) {
        if (t[i] != '0' && t[i] != '1') {
            delete[] _data;
            throw std::logic_error("Not 0-1 digit.");
        }
        _data[i] = t[i];
    }
    _size = t.size();
    shrink();
}

BitString::BitString(const BitString &other) {
    _size = other._size;
    _data = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
    shrink();
}

BitString::BitString(BitString &&other) noexcept {
    _size = other._size;
    _data = other._data;

    other._size = 0;
    other._data = 0;
    shrink();
}

BitString &BitString::operator=(const BitString &other) {
    if (this == &other) {
        return *this;
    }

    delete[] _data;
    _size = other._size;
    _data = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
    shrink();
    return *this;
}

BitString &BitString::operator=(BitString &&other) {
    delete[] _data;
    _size = other._size;
    _data = other._data;

    other._size = 0;
    other._data = nullptr;
    shrink();
    return *this;
}

BitString::BitString(const std::initializer_list<unsigned char> &t) {
    _size = t.size();
    _data = new unsigned char[_size];

    size_t i = 0;
    for (const auto value : t) {
        if (value != '0' && value != '1') {
            delete[] _data;
            throw std::logic_error("Not 0-1 digit.");
        }
        _data[i++] = value;
    }
    shrink();
}

BitString::~BitString() {
    if (_data) {
        delete[] _data;
    }
}

BitString &BitString::operator+=(const BitString &other) {
    size_t res_size = (_size < other._size) ? other._size : _size;
    unsigned char *result = new unsigned char[res_size + 1];
    result[0] = '0';
    int remain = 0;
    for (size_t i = 1; i <= res_size; ++i) {
        if (_size >= i) {
            remain += get_int(_data[_size - i]);
        }
        if (other._size >= i) {
            remain += get_int(other._data[other._size - i]);
        }
        result[res_size - i + 1] = get_char(remain % 2);
        remain /= 2;
    }
    if (remain) {
        result[0] = '1';
    }
    delete[] _data;
    _size = res_size + 1;
    _data = result;
    shrink();
    return *this;
};

BitString BitString::operator+(const BitString &other) const {
    BitString tmp(*this);
    tmp += other;
    return tmp;
}

BitString &BitString::operator-=(const BitString &other) {
    if (*this < other) {
        throw std::logic_error("BitString can only operate with not negative numbers.");
    }
    int taking = 0;
    for (size_t i = 1; i <= other._size; ++i) {
        int temp_int = _data[_size - i] - other._data[other._size - i] - taking;
        if (temp_int < 0) {
            temp_int = (2 + temp_int) % 2;
            taking = 1;
        } else {
            taking = 0;
        }
        _data[_size - i] = get_char(temp_int);
    }
    for (size_t i = _size - other._size; i > 0; --i) {
        int temp_int = get_int(_data[i - 1]) - taking;
        if (temp_int < 0) {
            temp_int = (2 + temp_int) % 2;
            taking = 1;
        } else {
            taking = 0;
        }
        _data[i - 1] = get_char(temp_int);
    }
    shrink();
    return *this;
}

BitString BitString::operator-(const BitString &other) const {
    BitString tmp(*this);
    tmp -= other;
    return tmp;
}

BitString BitString::operator&(const BitString &other) const {
    size_t res_size = (_size < other._size) ? other._size : _size;
    BitString result;
    result._data = new unsigned char[res_size];
    result._size = res_size;
    for (size_t i = 1; i <= res_size; ++i) {
        if (_size < i && other._size >= i) {
            result._data[res_size - i] = get_char(get_int(other._data[other._size - i]) & 0);
            continue;
        }
        if (other._size < i && _size >= i) {
            result._data[res_size - i] = get_char(get_int(_data[_size - i]) & 0);
            continue;
        }
        result._data[res_size - i] = get_char(get_int(_data[_size - i]) & get_int(other._data[other._size - i]));
    }
    result.shrink();
    return result;
}

BitString BitString::operator|(const BitString &other) const {
    size_t res_size = (_size < other._size) ? other._size : _size;
    BitString result;
    result._data = new unsigned char[res_size];
    result._size = res_size;
    for (size_t i = 1; i <= res_size; ++i) {
        if (_size < i && other._size >= i) {
            result._data[res_size - i] = get_char(get_int(other._data[other._size - i]) | 0);
            continue;
        }
        if (other._size < i && _size >= i) {
            result._data[res_size - i] = get_char(get_int(_data[_size - i]) | 0);
            continue;
        }
        result._data[res_size - i] = get_char(get_int(_data[_size - i]) | get_int(other._data[other._size - i]));
    }
    return result;
}

BitString BitString::operator^(const BitString &other) const {
    size_t res_size = (_size < other._size) ? other._size : _size;
    BitString result;
    result._data = new unsigned char[res_size];
    result._size = res_size;
    for (size_t i = 1; i <= res_size; ++i) {
        if (_size < i && other._size >= i) {
            result._data[res_size - i] = get_char(get_int(other._data[other._size - i]) ^ 0);
            continue;
        }
        if (other._size < i && _size >= i) {
            result._data[res_size - i] = get_char(get_int(_data[_size - i]) ^ 0);
            continue;
        }
        result._data[res_size - i] = get_char(get_int(_data[_size - i]) ^ get_int(other._data[other._size - i]));
    }
    result.shrink();
    return result;
}

BitString BitString::operator~() const {
    BitString result;
    result._data = new unsigned char[_size];
    result._size = _size;
    for (size_t i = 0; i < _size; ++i) {
        result._data[i] = get_char(get_int(_data[i]) ^ 1);
    }
    result.shrink();
    return result;
}

bool BitString::operator>(const BitString &other) const {
    if (_size > other._size) {
        return true;
    }
    if (_size < other._size) {
        return false;
    }
    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] > other._data[i]) {
            return true;
        }
        if (_data[i] < other._data[i]) {
            return false;
        }
    }
    return false;
}

bool BitString::operator<(const BitString &other) const {
    if (_size < other._size) {
        return true;
    }
    if (_size > other._size) {
        return false;
    }
    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] < other._data[i]) {
            return true;
        }
        if (_data[i] > other._data[i]) {
            return false;
        }
    }
    return false;
}

bool BitString::operator==(const BitString &other) const {
    if (_size != other._size) {
        return false;
    }
    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] != other._data[i]) {
            return false;
        }
    }
    return true;
}

bool BitString::operator!=(const BitString &other) const {
    return !(*this == other);
}

size_t BitString::getSize() const {
    return _size;
}

unsigned char BitString::getBit(size_t index) const {
    if (index < 0 || index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

void BitString::setBit(size_t index, unsigned char value) {
    if (index < 0 || index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    if (value != '0' && value != '1') {
        throw std::logic_error("Not 0-1 digit.");
    }
    _data[index] = value;
    shrink();
}

void BitString::shrink() {
    size_t z = 0;
    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] == '0') {
            ++z;
        } else {
            break;
        }
    }

    if (z == 0) {
        return;
    }

    if (z == _size) {
        delete[] _data;
        _data = new unsigned char[1];
        _data[0] = '0';
        _size = 1;
        return;
    }

    unsigned char *_temp_array = new unsigned char[_size - z];
    for (size_t i = z; i < _size; ++i) {
        _temp_array[i - z] = _data[i];
    }
    delete[] _data;
    _data = _temp_array;
    _size -= z;
}

std::ostream &operator<<(std::ostream &out, const BitString &b) {
    for (size_t i = 0; i < b._size; ++i)
        out << b._data[i];
    return out;
}