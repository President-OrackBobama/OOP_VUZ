#include <iostream>
#include <cmath>
#include "../include/FigureList.hpp"


size_t FigureList::size() const {
    return figures.size();
}

std::istream &operator>>(std::istream &in, FigureList &a) {
    size_t quantity;
    in >> quantity;
    char figure_type = '\0';
    for (size_t i = 0; i < quantity; ++i) {
        in >> figure_type;
        if (figure_type == 'T') {
            auto *t = new Triangle();
            in >> *t;
            a.figures.push_back(t);
        } else if (figure_type == 'H') {
            auto *h = new Hexagon();
            in >> *h;
            a.figures.push_back(h);
        } else if (figure_type == 'O') {
            auto *o = new Octagon();
            in >> *o;
            a.figures.push_back(o);
        } else {
            throw std::logic_error("Invalid or missed figure type");
        }
    }

    return in;
}

std::ostream &operator<<(std::ostream &out, FigureList &a) {
    for (size_t i = 0; i < a.size(); ++i) {
        out << static_cast<double>(*(a.figures[i])) << std::endl;
    }
    return out;
}

void FigureList::print_geom_center() const {
    for (size_t i = 0; i < size(); ++i) {
        Point a = figures[i]->geom_center();
        std::cout << a << std::endl;
    }
}

double FigureList::total_area() const {
    double current_area = 0;
    for (size_t i = 0; i < size(); ++i) {
        current_area += figures[i]->area();
    }
    return current_area;
}

FigureList::operator double() const {
    double current_area = 0;
    for (size_t i = 0; i < size(); ++i) {
        current_area += figures[i]->area();
    }
    return current_area;
}

void FigureList::erase(size_t index) {
    figures.erase(index);
}

void FigureList::push_back(Figure *a) {
    figures.push_back(a);
}




