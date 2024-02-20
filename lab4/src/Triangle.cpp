#include <iostream>
#include <cmath>
#include <cfloat>
#include "../include/Triangle.hpp"

template<typename T>
Triangle<T>::Triangle(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3) : p1(p1), p2(p2), p3(p3) {
    side = p1.dist(p2);

    bool c1 = fabs(p2.dist(p3) - side) > DBL_EPSILON;
    bool c2 = fabs(p3.dist(p1) - side) > DBL_EPSILON;
    if (c1 || c2) {
        throw std::logic_error("Triangle with given points does not have equal sides");
    }
}

template<typename T>
Triangle<T>::Triangle(T side) : side(side) {
    if (side <= 0) {
        throw std::logic_error("Side must be a positive number");
    }
    T R = side / (2 * sin(M_PI / 3));
    p1 = Point(R * std::cos(1 * 2 * M_PI / 3), R * std::sin(1 * 2 * M_PI / 3));
    p2 = Point(R * std::cos(2 * 2 * M_PI / 3), R * std::sin(2 * 2 * M_PI / 3));
    p3 = Point(R * std::cos(3 * 2 * M_PI / 3), R * std::sin(3 * 2 * M_PI / 3));
}

template<typename T>
Triangle<T>::Triangle(const Triangle<T> &other) {
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
    side = other.side;
}

template<typename T>
Triangle<T>::Triangle(Triangle<T> &&other) noexcept {
    p1 = std::move(other.p1);
    p2 = std::move(other.p2);
    p3 = std::move(other.p3);
    side = std::move(other.side);
}

template<typename T>
Triangle<T> &Triangle<T>::operator=(const Triangle<T> &other) {
    if (this != &other) {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
        side = other.side;
    }

    return *this;
}

template<typename T>
Triangle<T> &Triangle<T>::operator=(Triangle<T> &&other) noexcept {
    p1 = std::move(other.p1);
    p2 = std::move(other.p2);
    p3 = std::move(other.p3);
    side = std::move(other.side);

    return *this;
}

template<typename T>
bool Triangle<T>::operator==(const Triangle<T> &other) {
    return (p1 == other.p1 && p2 == other.p2 && p3 == other.p3);
}

template<typename U>
std::istream &operator>>(std::istream &in, Triangle<U> &a) {
    Point<U> p1, p2, p3;
    in >> p1 >> p2 >> p3;
    a = Triangle<U>(p1, p2, p3);

    return in;
}

template<typename U>
std::ostream &operator<<(std::ostream &out, Triangle<U> &a) {
    out << a.p1 << " " << a.p2 << " " << a.p3;
    return out;
}

template<typename T>
Point<T> Triangle<T>::geom_center() const {
    return {(p1.get_x() + p2.get_x() + p3.get_x()) / 3,
            (p1.get_y() + p2.get_y() + p3.get_y()) / 3};
}

template<typename T>
T Triangle<T>::area() const {
    return (side * side * sqrt(3)) / 4;
}

template<typename T>
Triangle<T>::operator double() const {
    return (side * side * sqrt(3)) / 4;
}
