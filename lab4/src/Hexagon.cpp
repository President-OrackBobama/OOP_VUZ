#include <iostream>
#include <cmath>
#include <cfloat>
#include "../include/Hexagon.hpp"

template<typename T>
Hexagon<T>::Hexagon(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3,
                 const Point<T> &p4, const Point<T> &p5, const Point<T> &p6) : p1(p1), p2(p2), p3(p3), p4(p4), p5(p5), p6(p6) {
    side = p1.dist(p2);
    bool c1 = fabs(p2.dist(p3) - side) > FLT_EPSILON;
    bool c2 = fabs(p3.dist(p4) - side) > FLT_EPSILON;
    bool c3 = fabs(p4.dist(p5) - side) > FLT_EPSILON;
    bool c4 = fabs(p5.dist(p6) - side) > FLT_EPSILON;
    bool c5 = fabs(p6.dist(p1) - side) > FLT_EPSILON;
    if (c1 || c2 || c3 || c4 || c5) {
        throw std::logic_error("Hexagon with given points does not have equal sides");
    }
}

template<typename T>
Hexagon<T>::Hexagon(T side) : side(side) {
    if (side <= 0) {
        throw std::logic_error("Side must be a positive number");
    }
    T R = side;
    p1 = Point<T>(R * std::cos(1 * 2 * M_PI / 6), R * std::sin(1 * 2 * M_PI / 6));
    p2 = Point<T>(R * std::cos(2 * 2 * M_PI / 6), R * std::sin(2 * 2 * M_PI / 6));
    p3 = Point<T>(R * std::cos(3 * 2 * M_PI / 6), R * std::sin(3 * 2 * M_PI / 6));
    p4 = Point<T>(R * std::cos(4 * 2 * M_PI / 6), R * std::sin(4 * 2 * M_PI / 6));
    p5 = Point<T>(R * std::cos(5 * 2 * M_PI / 6), R * std::sin(5 * 2 * M_PI / 6));
    p6 = Point<T>(R * std::cos(6 * 2 * M_PI / 6), R * std::sin(6 * 2 * M_PI / 6));
}

template<typename T>
Hexagon<T>::Hexagon(const Hexagon<T> &other) {
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
    p4 = other.p4;
    p5 = other.p5;
    p6 = other.p6;
    side = other.side;
}

template<typename T>
Hexagon<T>::Hexagon(Hexagon<T> &&other) noexcept {
    p1 = std::move(other.p1);
    p2 = std::move(other.p2);
    p3 = std::move(other.p3);
    p4 = std::move(other.p4);
    p5 = std::move(other.p5);
    p6 = std::move(other.p6);
    side = std::move(other.side);
}

template<typename T>
Hexagon<T> &Hexagon<T>::operator=(const Hexagon<T> &other) {
    if (this != &other) {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
        p4 = other.p4;
        p5 = other.p5;
        p6 = other.p6;
        side = other.side;
    }

    return *this;
}

template<typename T>
Hexagon<T> &Hexagon<T>::operator=(Hexagon<T> &&other) noexcept {
    p1 = std::move(other.p1);
    p2 = std::move(other.p2);
    p3 = std::move(other.p3);
    p4 = std::move(other.p4);
    p5 = std::move(other.p5);
    p6 = std::move(other.p6);
    side = std::move(other.side);

    return *this;
}

template<typename T>
bool Hexagon<T>::operator==(const Hexagon<T> &other) {
    return (p1 == other.p1 && p2 == other.p2 && p3 == other.p3 &&
            p4 == other.p4 && p5 == other.p5 && p6 == other.p6);
}

template<typename U>
std::istream &operator>>(std::istream &in, Hexagon<U> &a) {
    Point<U> p1, p2, p3, p4, p5, p6;
    in >> p1 >> p2 >> p3 >> p4 >> p5 >> p6;
    a = Hexagon<U>(p1, p2, p3, p4, p5, p6);

    return in;
}

template<typename U>
std::ostream &operator<<(std::ostream &out, Hexagon<U> &a) {
    out << a.p1 << " " << a.p2 << " " << a.p3 << " " << a.p4 << " " << a.p5 << " " << a.p6;
    return out;
}

template<typename T>
Point<T> Hexagon<T>::geom_center() const {
    return {(p1.get_x() + p2.get_x() + p3.get_x() + p4.get_x() + p5.get_x() + p6.get_x()) / 6,
            (p1.get_y() + p2.get_y() + p3.get_y() + p4.get_y() + p5.get_y() + p6.get_y()) / 6};
}

template<typename T>
T Hexagon<T>::area() const {
    return (side * side * 3 * sqrt(3)) / 2;
}

template<typename T>
Hexagon<T>::operator double() const {
    return (side * side * 3 * sqrt(3)) / 2;
}
