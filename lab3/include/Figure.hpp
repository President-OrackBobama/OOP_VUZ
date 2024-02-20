#pragma once

#include "Point.hpp"

class Figure {
protected:
    Figure() = default;

public:
    virtual ~Figure() = default;

    virtual Point geom_center() const = 0;
    virtual double area() const = 0;
    virtual operator double() const = 0;

};


