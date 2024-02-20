#include <iostream>
#include <cmath>
#include <cfloat>
#include "../include/Hexagon.hpp"

Hexagon::Hexagon(const Point &p1, const Point &p2, const Point &p3,
                 const Point &p4, const Point &p5, const Point &p6) : p1(p1), p2(p2), p3(p3), p4(p4), p5(p5), p6(p6) {
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

Hexagon::Hexagon(double side) : side(side) {
    if (side <= 0) {
        throw std::logic_error("Side must be a positive number");
    }
    double R = side;
    p1 = Point(R * std::cos(1 * 2 * M_PI / 6), R * std::sin(1 * 2 * M_PI / 6));
    p2 = Point(R * std::cos(2 * 2 * M_PI / 6), R * std::sin(2 * 2 * M_PI / 6));
    p3 = Point(R * std::cos(3 * 2 * M_PI / 6), R * std::sin(3 * 2 * M_PI / 6));
    p4 = Point(R * std::cos(4 * 2 * M_PI / 6), R * std::sin(4 * 2 * M_PI / 6));
    p5 = Point(R * std::cos(5 * 2 * M_PI / 6), R * std::sin(5 * 2 * M_PI / 6));
    p6 = Point(R * std::cos(6 * 2 * M_PI / 6), R * std::sin(6 * 2 * M_PI / 6));
}

Hexagon::Hexagon(const Hexagon &other) {
    p1 = other.p1;
    p2 = other.p2;
    p3 = other.p3;
    p4 = other.p4;
    p5 = other.p5;
    p6 = other.p6;
    side = other.side;
}

Hexagon::Hexagon(Hexagon &&other) noexcept {
    p1 = std::move(other.p1);
    p2 = std::move(other.p2);
    p3 = std::move(other.p3);
    p4 = std::move(other.p4);
    p5 = std::move(other.p5);
    p6 = std::move(other.p6);
    side = std::move(other.side);
}

Hexagon &Hexagon::operator=(const Hexagon &other) {
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

Hexagon &Hexagon::operator=(Hexagon &&other) noexcept {
    p1 = std::move(other.p1);
    p2 = std::move(other.p2);
    p3 = std::move(other.p3);
    p4 = std::move(other.p4);
    p5 = std::move(other.p5);
    p6 = std::move(other.p6);
    side = std::move(other.side);

    return *this;
}

bool Hexagon::operator==(const Hexagon &other) {
    return (p1 == other.p1 && p2 == other.p2 && p3 == other.p3 &&
            p4 == other.p4 && p5 == other.p5 && p6 == other.p6);
}

std::istream &operator>>(std::istream &in, Hexagon &a) {
    Point p1, p2, p3, p4, p5, p6;
    in >> p1 >> p2 >> p3 >> p4 >> p5 >> p6;
    a = Hexagon(p1, p2, p3, p4, p5, p6);

    return in;
}

std::ostream &operator<<(std::ostream &out, Hexagon &a) {
    out << a.p1 << " " << a.p2 << " " << a.p3 << " " << a.p4 << " " << a.p5 << " " << a.p6;
    return out;
}

Point Hexagon::geom_center() const {
    return {(p1.get_x() + p2.get_x() + p3.get_x() + p4.get_x() + p5.get_x() + p6.get_x()) / 6,
            (p1.get_y() + p2.get_y() + p3.get_y() + p4.get_y() + p5.get_y() + p6.get_y()) / 6};
}

double Hexagon::area() const {
    return (side * side * 3 * sqrt(3)) / 2;
}

Hexagon::operator double() const {
    return (side * side * 3 * sqrt(3)) / 2;
}
