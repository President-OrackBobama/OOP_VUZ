#pragma once

template<typename T>
class Point {
private:
    T x;
    T y;

public:

    Point() = default;
    Point(T x, T y);
    Point(const Point& other);
    Point(Point&& other);
    Point& operator=(const Point& other);
    T dist(const Point& other) const;
    bool operator==(const Point& other) const;

    T get_x() const;
    T get_y() const;

    void set_x(T _x);
    void set_y(T _y);

    template<typename U>
    friend std::istream& operator>>(std::istream& in, Point<U>& a);
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, Point<U>& a);

};

