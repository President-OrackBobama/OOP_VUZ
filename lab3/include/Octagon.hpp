#pragma once


#include "Point.hpp"
#include "Figure.hpp"

class Octagon: public Figure {
private:
    Point p1{}, p2{}, p3{}, p4{}, p5{}, p6{}, p7{}, p8{};
    double side{};

public:

    Octagon() = default;
    Octagon(const Point &p1, const Point &p2, const Point &p3, const Point &p4,
            const Point &p5, const Point &p6, const Point &p7, const Point &p8);
    explicit Octagon(double side);
    Octagon(const Octagon& other);
    Octagon(Octagon&& other) noexcept;
    Octagon& operator=(const Octagon& other);
    Octagon& operator=(Octagon&& other) noexcept;

    bool operator==(const Octagon& other);
    friend std::istream& operator>>(std::istream& in, Octagon& a);
    friend std::ostream& operator<<(std::ostream& out, Octagon& a);

    virtual Point geom_center() const override;
    virtual double area() const override;
    virtual operator double() const override;


};
