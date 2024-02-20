#pragma once


#include "Point.hpp"
#include "Figure.hpp"

class Triangle: public Figure {
private:
    Point p1{}, p2{}, p3{};
    double side{};

public:

    Triangle() = default;
    Triangle(const Point& p1, const Point& p2, const Point& p3);
    explicit Triangle(double side);
    Triangle(const Triangle& other);
    Triangle(Triangle&& other) noexcept;
    Triangle& operator=(const Triangle& other);
    Triangle& operator=(Triangle&& other) noexcept;

    bool operator==(const Triangle& other);
    friend std::istream& operator>>(std::istream& in, Triangle& a);
    friend std::ostream& operator<<(std::ostream& out, Triangle& a);

    virtual Point geom_center() const override;
    virtual double area() const override;
    virtual operator double() const override;


};

