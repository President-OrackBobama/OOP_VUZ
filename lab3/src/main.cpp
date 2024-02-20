#include <iostream>
#include <cmath>

#include "Triangle.cpp"
#include "Hexagon.cpp"
#include "Octagon.cpp"
#include "FigureList.cpp"
#include "Point.cpp"
#include "Vector.cpp"

int main() {

    /*
    Triangle t0;
    std::cin >> t0;
    Point p0 = t0.geom_center();
    std::cout << t0 << std::endl;
    std::cout << p0 << std::endl;
    std::cout << t0.area() << std::endl << std::endl;
    */

    Triangle t1(Point(1, sqrt(3)), Point(2, 0), Point(0, 0));
    Point p1 = t1.geom_center();
    std::cout << t1 << std::endl;
    std::cout << p1 << std::endl;
    std::cout << t1.area() << std::endl << std::endl;

    Triangle t2(2);
    Point p2 = t2.geom_center();
    std::cout << t2 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << t2.area() << std::endl << std::endl;

    Hexagon h1(3);
    Point p3 = h1.geom_center();
    std::cout << h1 << std::endl;
    std::cout << p3 << std::endl;
    std::cout << h1.area() << std::endl << std::endl;

    Octagon o1(4);
    Point p4 = o1.geom_center();
    std::cout << o1 << std::endl;
    std::cout << p4 << std::endl;
    std::cout << o1.area() << std::endl << std::endl;

    FigureList fl{};
    fl.push_back(&t1);
    fl.push_back(&t2);
    fl.push_back(&h1);
    fl.push_back(&o1);

    fl.print_geom_center();
    std::cout << fl.total_area() << std::endl;

    return 0;
}
