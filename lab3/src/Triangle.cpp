#include <iostream>
#include <cmath>
#include <cfloat>
#include "../include/Triangle.hpp"

Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3) : p1(p1), p2(p2), p3(p3) {
    side = p1.dist(p2);

    bool c1 = fabs(p2.dist(p3) - side) > DBL_EPSILON;
    bool c2 = fabs(p3.dist(p1) - side) > DBL_EPSILON;
    if (c1 || c2) {
        throw std::logic_error("Triangle with given points does not have equal sides");
    }
}

Triangle::Triangle(double side) : side(side) {
    if (side <= 0) {
        throw std::logic_error("Side must be a positive number");
    }
    double R = side / (2 * sin(M_PI / 3));
    p1 = Point(R * std::cos(1 * 2 * M_PI / 3), R * std::sin(1 * 2 * M_PI / 3));
    p2 = Point(R * std::cos(2 * 2 * M_PI / 3), R * std::sin(2 * 2 * M_PI / 3));
    p3 = Point(R * std::cos(3 * 2 * M_PI / 3), R * std::sin(3 * 2 * M_PI / 3));
}

Triangle::Triangle(const Triangle &other) {
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
    side = other.side;
}

Triangle::Triangle(Triangle &&other) noexcept {
    p1 = std::move(other.p1);
    p2 = std::move(other.p2);
    p3 = std::move(other.p3);
    side = std::move(other.side);
}

Triangle &Triangle::operator=(const Triangle &other) {
    if (this != &other) {
        p1 = other.p1;
        p2 = other.p2;
        p3 = other.p3;
        side = other.side;
    }

    return *this;
}

Triangle &Triangle::operator=(Triangle &&other) noexcept {
    p1 = std::move(other.p1);
    p2 = std::move(other.p2);
    p3 = std::move(other.p3);
    side = std::move(other.side);

    return *this;
}

bool Triangle::operator==(const Triangle &other) {
    return (p1 == other.p1 && p2 == other.p2 && p3 == other.p3);
}

std::istream &operator>>(std::istream &in, Triangle &a) {
    Point p1, p2, p3;
    in >> p1 >> p2 >> p3;
    a = Triangle(p1, p2, p3);

    return in;
}

std::ostream &operator<<(std::ostream &out, Triangle &a) {
    out << a.p1 << " " << a.p2 << " " << a.p3;
    return out;
}

Point Triangle::geom_center() const {
    return {(p1.get_x() + p2.get_x() + p3.get_x()) / 3,
            (p1.get_y() + p2.get_y() + p3.get_y()) / 3};
}

double Triangle::area() const {
    return (side * side * sqrt(3)) / 4;
}

Triangle::operator double() const {
    return (side * side * sqrt(3)) / 4;
}
