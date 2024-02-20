#pragma once

#include "Point.hpp"
#include "Figure.hpp"

template<typename T>
class Triangle: public Figure<T> {
public:
    Point<T> p1{}, p2{}, p3{};
    T side{};

public:

    Triangle() = default;
    Triangle(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3);
    explicit Triangle(T side);
    Triangle(const Triangle& other);
    Triangle(Triangle&& other) noexcept;
    Triangle& operator=(const Triangle& other);
    Triangle& operator=(Triangle&& other) noexcept;

    bool operator==(const Triangle& other);

    template<typename U>
    friend std::istream& operator>>(std::istream& in, Triangle& a);
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, Triangle& a);

    virtual Point<T> geom_center() const override;
    virtual T area() const override;
    virtual operator double() const override;


};
