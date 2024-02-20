#include <iostream>
#include <cmath>
#include <iomanip>

#include "Triangle.cpp"
#include "Hexagon.cpp"
#include "Octagon.cpp"
#include "FigureArray.cpp"
#include "Point.cpp"

int main() {

    /* Testing figure creation from input
    Triangle t0;
    std::cin >> t0;
    Point p0 = t0.geom_center();
    std::cout << t0 << std::endl;
    std::cout << p0 << std::endl;
    std::cout << t0.area() << std::endl << std::endl;
    */

    std::cout << std::setprecision(20);
    Triangle<double> t1(Point<double>(1, sqrt(3)),
                        Point<double>(2, 0),
                        Point<double>(0, 0));
    Point<double> p1 = t1.geom_center();
    std::cout << t1 << std::endl;
    std::cout << p1 << std::endl;
    std::cout << t1.area() << std::endl << std::endl;

    Triangle<double> t2(2);
    Point p2 = t2.geom_center();
    std::cout << t2 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << t2.area() << std::endl << std::endl;

    Hexagon<double> h1(3);
    Point p3 = h1.geom_center();
    std::cout << h1 << std::endl;
    std::cout << p3 << std::endl;
    std::cout << h1.area() << std::endl << std::endl;


    Octagon<double> o1(4);
    Point p4 = o1.geom_center();
    std::cout << o1 << std::endl;
    std::cout << p4 << std::endl;
    std::cout << o1.area() << std::endl << std::endl;

    /*
    FigureArray<double> fa{};
    std::cin >> fa;

    // fa.erase(0);
    std::cout << fa.total_area() << std::endl;
    */


    return 0;
}
