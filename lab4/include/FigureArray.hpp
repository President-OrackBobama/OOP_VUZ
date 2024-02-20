#pragma once


#include "Figure.hpp"
#include "Triangle.hpp"
#include <memory>

template<typename T>
class FigureArray {
private:
    std::shared_ptr<std::shared_ptr<Figure<T>>[]> figures;
    size_t sz = 0;

public:
    FigureArray();
    FigureArray(std::initializer_list<std::shared_ptr<Figure<T>>> list);
    FigureArray(const FigureArray<T>& other);
    FigureArray(FigureArray<T>&& other) noexcept ;
    size_t size() const;

    template<typename U>
    friend std::istream& operator>>(std::istream& in, FigureArray<U>& a);
    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, FigureArray<U>& a);

    void print_geom_center() const;
    T total_area() const;
    operator double() const;

    void erase(size_t index);

};



