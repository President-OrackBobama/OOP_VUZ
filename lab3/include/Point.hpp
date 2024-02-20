#pragma once


class Point {
private:
    double x;
    double y;

public:

    Point() = default;
    Point(double x, double y);
    Point(const Point& other);
    Point(Point&& other);
    Point& operator=(const Point& other);
    double dist(const Point& other) const;
    bool operator==(const Point& other) const;

    double get_x() const;
    double get_y() const;

    void set_x(double _x);
    void set_y(double _y);

    friend std::istream& operator>>(std::istream& in, Point& a);
    friend std::ostream& operator<<(std::ostream& out, Point& a);

};

