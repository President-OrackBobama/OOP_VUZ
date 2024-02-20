#pragma once


#include "Point.hpp"
#include "Figure.hpp"

class Hexagon: public Figure {
private:
    Point p1{}, p2{}, p3{}, p4{}, p5{}, p6{};
    double side{};

public:

    Hexagon() = default;
    Hexagon(const Point &p1, const Point &p2, const Point &p3,
            const Point &p4, const Point &p5, const Point &p6);
    explicit Hexagon(double side);
    Hexagon(const Hexagon& other);
    Hexagon(Hexagon&& other) noexcept;
    Hexagon& operator=(const Hexagon& other);
    Hexagon& operator=(Hexagon&& other) noexcept;

    bool operator==(const Hexagon& other);
    friend std::istream& operator>>(std::istream& in, Hexagon& a);
    friend std::ostream& operator<<(std::ostream& out, Hexagon& a);

    virtual Point geom_center() const override;
    virtual double area() const override;
    virtual operator double() const override;


};


