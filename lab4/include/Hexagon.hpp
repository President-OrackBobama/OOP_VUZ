#pragma once


#include "Point.hpp"
#include "Figure.hpp"

template<typename T>
class Hexagon: public Figure<T> {
private:
    Point<T> p1{}, p2{}, p3{}, p4{}, p5{}, p6{};
    double side{};

public:

    Hexagon() = default;
    Hexagon(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3,
            const Point<T> &p4, const Point<T> &p5, const Point<T> &p6);
    explicit Hexagon(T side);
    Hexagon(const Hexagon& other);
    Hexagon(Hexagon&& other) noexcept;
    Hexagon& operator=(const Hexagon& other);
    Hexagon& operator=(Hexagon&& other) noexcept;

    bool operator==(const Hexagon& other);
    template<typename U>
    friend std::istream& operator>>(std::istream& in, Hexagon<U>& a);
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, Hexagon<U>& a);

    virtual Point<T> geom_center() const override;
    virtual T area() const override;
    virtual operator double() const override;


};