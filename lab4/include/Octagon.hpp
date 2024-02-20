#pragma once

#include "Point.hpp"
#include "Figure.hpp"

template<typename T>
class Octagon: public Figure<T> {
private:
    Point<T> p1{}, p2{}, p3{}, p4{}, p5{}, p6{}, p7{}, p8{};
    double side{};

public:

    Octagon() = default;
    Octagon(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3, const Point<T> &p4,
            const Point<T> &p5, const Point<T> &p6, const Point<T> &p7, const Point<T> &p8);
    explicit Octagon(T side);
    Octagon(const Octagon& other);
    Octagon(Octagon&& other) noexcept;
    Octagon& operator=(const Octagon& other);
    Octagon& operator=(Octagon&& other) noexcept;

    bool operator==(const Octagon& other);
    template<typename U>
    friend std::istream& operator>>(std::istream& in, Octagon<U>& a);
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, Octagon<U>& a);

    virtual Point<T> geom_center() const override;
    virtual T area() const override;
    virtual operator double() const override;

};
