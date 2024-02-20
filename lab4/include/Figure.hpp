#pragma once
#include "Point.hpp"

template<typename T>
class Figure {
protected:
    Figure() = default;

public:
    virtual ~Figure() = default;

    virtual Point<T> geom_center() const = 0;
    virtual T area() const = 0;
    virtual operator double() const = 0;

};

