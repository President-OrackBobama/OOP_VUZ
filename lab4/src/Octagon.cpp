#include <iostream>
#include <cmath>
#include <cfloat>
#include "../include/Octagon.hpp"

template<typename T>
Octagon<T>::Octagon(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3, const Point<T> &p4,
                 const Point<T> &p5, const Point<T> &p6, const Point<T> &p7, const Point<T> &p8) : p1(p1), p2(p2), p3(p3), p4(p4),
                                                                                       p5(p5), p6(p6), p7(p7), p8(p8) {
    side = p1.dist(p2);

    bool c1 = fabs(p2.dist(p3) - side) > FLT_EPSILON;
    bool c2 = fabs(p3.dist(p4) - side) > FLT_EPSILON;
    bool c3 = fabs(p4.dist(p5) - side) > FLT_EPSILON;
    bool c4 = fabs(p5.dist(p6) - side) > FLT_EPSILON;
    bool c5 = fabs(p6.dist(p7) - side) > FLT_EPSILON;
    bool c6 = fabs(p7.dist(p8) - side) > FLT_EPSILON;
    bool c7 = fabs(p8.dist(p1) - side) > FLT_EPSILON;

    if (c1 || c2 || c3 || c4 || c5 || c6 || c7) {
        throw std::logic_error("Octagon with given Point<T>s does not have equal sides");
    }
}

template<typename T>
Octagon<T>::Octagon(T side) : side(side) {
    if (side <= 0) {
        throw std::logic_error("Side must be a positive number");
    }

    T R = side / (2 * sin(M_PI / 8));
    p1 = Point<T>(R * std::cos(1 * 2 * M_PI / 8), R * std::sin(1 * 2 * M_PI / 8));
    p2 = Point<T>(R * std::cos(2 * 2 * M_PI / 8), R * std::sin(2 * 2 * M_PI / 8));
    p3 = Point<T>(R * std::cos(3 * 2 * M_PI / 8), R * std::sin(3 * 2 * M_PI / 8));
    p4 = Point<T>(R * std::cos(4 * 2 * M_PI / 8), R * std::sin(4 * 2 * M_PI / 8));
    p5 = Point<T>(R * std::cos(5 * 2 * M_PI / 8), R * std::sin(5 * 2 * M_PI / 8));
    p6 = Point<T>(R * std::cos(6 * 2 * M_PI / 8), R * std::sin(6 * 2 * M_PI / 8));
    p7 = Point<T>(R * std::cos(7 * 2 * M_PI / 8), R * std::sin(7 * 2 * M_PI / 8));
    p8 = Point<T>(R * std::cos(8 * 2 * M_PI / 8), R * std::sin(8 * 2 * M_PI / 8));
}

template<typename T>
Octagon<T>::Octagon(const Octagon<T> &other) {
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
    p4 = other.p4;
    p5 = other.p5;
    p6 = other.p6;
    p7 = other.p7;
    p8 = other.p8;
    side = other.side;
}

template<typename T>
Octagon<T>::Octagon(Octagon<T> &&other) noexcept {
    p1 = std::move(other.p1);
    p2 = std::move(other.p2);
    p3 = std::move(other.p3);
    p4 = std::move(other.p4);
    p5 = std::move(other.p5);
    p6 = std::move(other.p6);
    p7 = std::move(other.p7);
    p8 = std::move(other.p8);
    side = std::move(other.side);
}

template<typename T>
Octagon<T> &Octagon<T>::operator=(const Octagon<T> &other) {
    if (this != &other) {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
        p4 = other.p4;
        p5 = other.p5;
        p6 = other.p6;
        p7 = other.p7;
        p8 = other.p8;
        side = other.side;
    }

    return *this;
}

template<typename T>
Octagon<T> &Octagon<T>::operator=(Octagon<T> &&other) noexcept {
    p1 = std::move(other.p1);
    p2 = std::move(other.p2);
    p3 = std::move(other.p3);
    p4 = std::move(other.p4);
    p5 = std::move(other.p5);
    p6 = std::move(other.p6);
    p7 = std::move(other.p7);
    p8 = std::move(other.p8);
    side = std::move(other.side);

    return *this;
}

template<typename T>
bool Octagon<T>::operator==(const Octagon<T> &other) {
    return (p1 == other.p1 && p2 == other.p2 && p3 == other.p3 && p4 == other.p4 &&
            p5 == other.p5 && p6 == other.p6 && p7 == other.p7 && p8 == other.p8);
}

template<typename U>
std::istream &operator>>(std::istream &in, Octagon<U> &a) {
    Point<U> p1, p2, p3, p4, p5, p6, p7, p8;
    in >> p1 >> p2 >> p3 >> p4 >> p5 >> p6 >> p7 >> p8;
    a = Octagon<U>(p1, p2, p3, p4, p5, p6, p7, p8);
    return in;
}

template<typename U>
std::ostream &operator<<(std::ostream &out, Octagon<U> &a) {
    out << a.p1 << " " << a.p2 << " " << a.p3 << " " << a.p4 <<
        " " << a.p5 << " " << a.p6 << " " << a.p7 << " " << a.p8;
    return out;
}

template<typename T>
Point<T> Octagon<T>::geom_center() const {
    return {(p1.get_x() + p2.get_x() + p3.get_x() + p4.get_x() +
             p5.get_x() + p6.get_x() + p7.get_x() + p8.get_x()) / 8,
            (p1.get_y() + p2.get_y() + p3.get_y() + p4.get_y() +
             p5.get_y() + p6.get_y() + p7.get_y() + p8.get_y()) / 8};
}

template<typename T>
T Octagon<T>::area() const {
    return 2 * side * side * (sqrt(2) + 1);
}

template<typename T>
Octagon<T>::operator double() const {
    return 2 * side * side * (sqrt(2) + 1);
}
