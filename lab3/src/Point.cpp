#include <iostream>
#include <cmath>
#include "../include/Point.hpp"

Point::Point(double x, double y): x(x), y(y) {}

double Point::dist(const Point &other) const {
    return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
}

std::istream &operator>>(std::istream &in, Point &a) {
    in >> a.x >> a.y;
    return in;
}

std::ostream &operator<<(std::ostream &out, Point &a) {
    const double eps = std::numeric_limits<float>::epsilon();
    // out << "(" << (fabs(a.x) < eps ? 0 : a.x) << ", " << (fabs(a.y) < eps ? 0 : a.y) << ")";
    out << "(" << a.x << ", " << a.y << ")";
    return out;
}

Point::Point(const Point &other) {
    x = other.x;
    y = other.y;
}

Point& Point::operator=(const Point &other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }

    return *this;
}

Point::Point(Point &&other) {
    x = std::move(other.x);
    y = std::move(other.y);
}

bool Point::operator==(const Point &other) const {
    return (x == other.x && y == other.y);
}

double Point::get_x() const {
    return x;
}

double Point::get_y() const {
    return y;
}

void Point::set_x(double _x) {
    x = _x;
}

void Point::set_y(double _y) {
    y = _y;
}
