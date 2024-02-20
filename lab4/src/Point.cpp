#include <iostream>
#include <cmath>
#include "../include/Point.hpp"

template<typename T>
Point<T>::Point(T x, T y): x(x), y(y) {}

template<typename T>
T Point<T>::dist(const Point<T> &other) const {
    return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
}

template<typename U>
std::istream &operator>>(std::istream &in, Point<U> &a) {
    in >> a.x >> a.y;
    return in;
}

template<typename U>
std::ostream &operator<<(std::ostream &out, Point<U> &a) {
    const U eps = std::numeric_limits<float>::epsilon();
    // out << "(" << (fabs(a.x) < eps ? 0 : a.x) << ", " << (fabs(a.y) < eps ? 0 : a.y) << ")";
    out << "(" << a.x << ", " << a.y << ")";
    return out;
}

template<typename T>
Point<T>::Point(const Point<T> &other) {
    x = other.x;
    y = other.y;
}

template<typename T>
Point<T>& Point<T>::operator=(const Point<T> &other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }

    return *this;
}

template<typename T>
Point<T>::Point(Point<T> &&other) {
    x = std::move(other.x);
    y = std::move(other.y);
}

template<typename T>
bool Point<T>::operator==(const Point<T> &other) const {
    return (x == other.x && y == other.y);
}

template<typename T>
T Point<T>::get_x() const {
    return x;
}

template<typename T>
T Point<T>::get_y() const {
    return y;
}

template<typename T>
void Point<T>::set_x(T _x) {
    x = _x;
}

template<typename T>
void Point<T>::set_y(T _y) {
    y = _y;
}
