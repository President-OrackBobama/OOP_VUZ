#include <iostream>
#include <cmath>
#include <cfloat>
#include "../include/Octagon.hpp"

Octagon::Octagon(const Point &p1, const Point &p2, const Point &p3, const Point &p4,
                 const Point &p5, const Point &p6, const Point &p7, const Point &p8) : p1(p1), p2(p2), p3(p3), p4(p4),
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
        throw std::logic_error("Octagon with given points does not have equal sides");
    }
}

Octagon::Octagon(double side) : side(side) {
    if (side <= 0) {
        throw std::logic_error("Side must be a positive number");
    }

    double R = side / (2 * sin(M_PI / 8));
    p1 = Point(R * std::cos(1 * 2 * M_PI / 8), R * std::sin(1 * 2 * M_PI / 8));
    p2 = Point(R * std::cos(2 * 2 * M_PI / 8), R * std::sin(2 * 2 * M_PI / 8));
    p3 = Point(R * std::cos(3 * 2 * M_PI / 8), R * std::sin(3 * 2 * M_PI / 8));
    p4 = Point(R * std::cos(4 * 2 * M_PI / 8), R * std::sin(4 * 2 * M_PI / 8));
    p5 = Point(R * std::cos(5 * 2 * M_PI / 8), R * std::sin(5 * 2 * M_PI / 8));
    p6 = Point(R * std::cos(6 * 2 * M_PI / 8), R * std::sin(6 * 2 * M_PI / 8));
    p7 = Point(R * std::cos(7 * 2 * M_PI / 8), R * std::sin(7 * 2 * M_PI / 8));
    p8 = Point(R * std::cos(8 * 2 * M_PI / 8), R * std::sin(8 * 2 * M_PI / 8));
}

Octagon::Octagon(const Octagon &other) {
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

Octagon::Octagon(Octagon &&other) noexcept {
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

Octagon &Octagon::operator=(const Octagon &other) {
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

Octagon &Octagon::operator=(Octagon &&other) noexcept {
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

bool Octagon::operator==(const Octagon &other) {
    return (p1 == other.p1 && p2 == other.p2 && p3 == other.p3 && p4 == other.p4 &&
            p5 == other.p5 && p6 == other.p6 && p7 == other.p7 && p8 == other.p8);
}

std::istream &operator>>(std::istream &in, Octagon &a) {
    Point p1, p2, p3, p4, p5, p6, p7, p8;
    in >> p1 >> p2 >> p3 >> p4 >> p5 >> p6 >> p7 >> p8;
    a = Octagon(p1, p2, p3, p4, p5, p6, p7, p8);
    return in;
}

std::ostream &operator<<(std::ostream &out, Octagon &a) {
    out << a.p1 << " " << a.p2 << " " << a.p3 << " " << a.p4 <<
        " " << a.p5 << " " << a.p6 << " " << a.p7 << " " << a.p8;
    return out;
}

Point Octagon::geom_center() const {
    return {(p1.get_x() + p2.get_x() + p3.get_x() + p4.get_x() +
             p5.get_x() + p6.get_x() + p7.get_x() + p8.get_x()) / 8,
            (p1.get_y() + p2.get_y() + p3.get_y() + p4.get_y() +
             p5.get_y() + p6.get_y() + p7.get_y() + p8.get_y()) / 8};
}

double Octagon::area() const {
    return 2 * side * side * (sqrt(2) + 1);
}

Octagon::operator double() const {
    return 2 * side * side * (sqrt(2) + 1);
}
