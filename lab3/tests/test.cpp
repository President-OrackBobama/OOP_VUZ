#include "gtest/gtest.h"
#include <cmath>
#include "../src/Point.cpp"
#include "../src/Vector.cpp"
#include "../src/Triangle.cpp"
#include "../src/Hexagon.cpp"
#include "../src/Octagon.cpp"

TEST(point_test, basic_test_set) {
    Point p1(1, 2);
    Point p2(3, 4);
    ASSERT_TRUE(fabs(p1.dist(p2) - (2 * sqrt(2))) < DBL_EPSILON);
    ASSERT_TRUE(fabs(Point().dist(Point())) < DBL_EPSILON);
}

// Tests for Triangle

TEST(triangle_test, default_constructor) {
    ASSERT_NO_THROW(Triangle());
}

TEST(triangle_test, point_constructor) {
    ASSERT_NO_THROW(Triangle(Point(1, sqrt(3)), Point(2, 0), Point(0, 0)));
    EXPECT_THROW(Triangle(Point(0, sqrt(3)), Point(2, 0), Point(0, 0)), std::logic_error);
}

TEST(triangle_test, side_constructor) {
    ASSERT_NO_THROW(Triangle(4));
    EXPECT_THROW(Triangle(-4), std::logic_error);
}

TEST(triangle_test, equality) {
    auto p1 = Point(1, sqrt(3));
    auto p2 = Point(2, 0);
    auto p3 = Point(0, 0);
    Triangle t0(Point(1, sqrt(3)), Point(2, 0), Point(0, 0));
    Triangle t1(Point(1, sqrt(3)), Point(2, 0), Point(0, 0));
    Triangle t2(t1);
    Triangle t3(p1, p2, p3);
    Triangle t4(Point(1 + 1, sqrt(3) + 1), Point(2 + 1, 0 + 1), Point(0 + 1, 0 + 1));

    ASSERT_TRUE(t1 == t0);
    ASSERT_TRUE(t2 == t0);
    ASSERT_TRUE(t3 == t1);
    ASSERT_FALSE(t4 == t1);
}

TEST(triangle_test, area_test) {
    Triangle t0(Point(1, sqrt(3)), Point(2, 0), Point(0, 0));
    Triangle t4(Point(1 + 1, sqrt(3) + 1), Point(2 + 1, 0 + 1), Point(0 + 1, 0 + 1));

    ASSERT_TRUE(fabs(t0.area() - (4 * sqrt(3) / 4)) <= FLT_EPSILON);
    ASSERT_TRUE(fabs(t4.area() - (4 * sqrt(3) / 4)) <= FLT_EPSILON);
}

TEST(triangle_test, double_test) {
    Triangle t0(Point(1, sqrt(3)), Point(2, 0), Point(0, 0));
    Triangle t4(Point(1 + 1, sqrt(3) + 1), Point(2 + 1, 0 + 1), Point(0 + 1, 0 + 1));

    ASSERT_TRUE(fabs(static_cast<double>(t0) - (4 * sqrt(3) / 4)) <= FLT_EPSILON);
    ASSERT_TRUE(fabs(static_cast<double>(t4) - (4 * sqrt(3) / 4)) <= FLT_EPSILON);
}

TEST(triangle_test, geom_center) {
    Triangle t0(Point(1, sqrt(3)), Point(2, 0), Point(0, 0));
    Triangle t4(Point(1 + 1, sqrt(3) + 1), Point(2 + 1, 0 + 1), Point(0 + 1, 0 + 1));

    ASSERT_TRUE(fabs(t0.geom_center().dist(Point(1, 1 / sqrt(3)))) <= FLT_EPSILON);
    ASSERT_TRUE(fabs(t4.geom_center().dist(Point(1 + 1, 1 / sqrt(3) + 1))) <= FLT_EPSILON);
}

// Tests for Hexagon

TEST(hexagon_test, default_constructor) {
    ASSERT_NO_THROW(Hexagon());
}

TEST(hexagon_test, point_constructor) {
    double R = 6;
    Point p1 = Point(R * std::cos(1 * 2 * M_PI / 6), R * std::sin(1 * 2 * M_PI / 6));
    Point p2 = Point(R * std::cos(2 * 2 * M_PI / 6), R * std::sin(2 * 2 * M_PI / 6));
    Point p3 = Point(R * std::cos(3 * 2 * M_PI / 6), R * std::sin(3 * 2 * M_PI / 6));
    Point p4 = Point(R * std::cos(4 * 2 * M_PI / 6), R * std::sin(4 * 2 * M_PI / 6));
    Point p5 = Point(R * std::cos(5 * 2 * M_PI / 6), R * std::sin(5 * 2 * M_PI / 6));
    Point p6 = Point(R * std::cos(6 * 2 * M_PI / 6), R * std::sin(6 * 2 * M_PI / 6));
    ASSERT_NO_THROW(Hexagon(p1, p2, p3, p4, p5, p6));
    EXPECT_THROW(Hexagon(Point(-100.0, -100.0), p2, p3, p4, p5, p6), std::logic_error);
}

TEST(hexagon_test, side_constructor) {
    ASSERT_NO_THROW(Hexagon(4));
    EXPECT_THROW(Hexagon(-4), std::logic_error);
}

TEST(hexagon_test, equality) {
    double R = 6;
    Point p1 = Point(R * std::cos(1 * 2 * M_PI / 6), R * std::sin(1 * 2 * M_PI / 6));
    Point p2 = Point(R * std::cos(2 * 2 * M_PI / 6), R * std::sin(2 * 2 * M_PI / 6));
    Point p3 = Point(R * std::cos(3 * 2 * M_PI / 6), R * std::sin(3 * 2 * M_PI / 6));
    Point p4 = Point(R * std::cos(4 * 2 * M_PI / 6), R * std::sin(4 * 2 * M_PI / 6));
    Point p5 = Point(R * std::cos(5 * 2 * M_PI / 6), R * std::sin(5 * 2 * M_PI / 6));
    Point p6 = Point(R * std::cos(6 * 2 * M_PI / 6), R * std::sin(6 * 2 * M_PI / 6));
    Hexagon h0(p1, p2, p3, p4, p5, p6);

    Hexagon h1(p1, p2, p3, p4, p5, p6);
    Hexagon h2(h1);
    Hexagon h3(146);

    ASSERT_TRUE(h1 == h0);
    ASSERT_TRUE(h2 == h0);
    ASSERT_FALSE(h3 == h1);
}


TEST(hexagon_test, area_test) {
    Hexagon h0(3);

    ASSERT_TRUE(fabs(h0.area() - (3 * 3 * 3 * sqrt(3) / 2)) <= FLT_EPSILON);
}

TEST(hexagon_test, double_test) {
    double R = 3;
    Point p1 = Point(R * std::cos(1 * 2 * M_PI / 6) + 2, R * std::sin(1 * 2 * M_PI / 6) + 2);
    Point p2 = Point(R * std::cos(2 * 2 * M_PI / 6) + 2, R * std::sin(2 * 2 * M_PI / 6) + 2);
    Point p3 = Point(R * std::cos(3 * 2 * M_PI / 6) + 2, R * std::sin(3 * 2 * M_PI / 6) + 2);
    Point p4 = Point(R * std::cos(4 * 2 * M_PI / 6) + 2, R * std::sin(4 * 2 * M_PI / 6) + 2);
    Point p5 = Point(R * std::cos(5 * 2 * M_PI / 6) + 2, R * std::sin(5 * 2 * M_PI / 6) + 2);
    Point p6 = Point(R * std::cos(6 * 2 * M_PI / 6) + 2, R * std::sin(6 * 2 * M_PI / 6) + 2);
    Hexagon h0(p1, p2, p3, p4, p5, p6);

    ASSERT_TRUE(fabs(static_cast<double>(h0) - (3 * 3 * 3 * sqrt(3) / 2)) <= FLT_EPSILON);
}


TEST(hexagon_test, geom_center) {
    Hexagon h0(3);

    double R = 6;
    Point p1 = Point(R * std::cos(1 * 2 * M_PI / 6) + 2, R * std::sin(1 * 2 * M_PI / 6) + 2);
    Point p2 = Point(R * std::cos(2 * 2 * M_PI / 6) + 2, R * std::sin(2 * 2 * M_PI / 6) + 2);
    Point p3 = Point(R * std::cos(3 * 2 * M_PI / 6) + 2, R * std::sin(3 * 2 * M_PI / 6) + 2);
    Point p4 = Point(R * std::cos(4 * 2 * M_PI / 6) + 2, R * std::sin(4 * 2 * M_PI / 6) + 2);
    Point p5 = Point(R * std::cos(5 * 2 * M_PI / 6) + 2, R * std::sin(5 * 2 * M_PI / 6) + 2);
    Point p6 = Point(R * std::cos(6 * 2 * M_PI / 6) + 2, R * std::sin(6 * 2 * M_PI / 6) + 2);
    Hexagon h1(p1, p2, p3, p4, p5, p6);

    ASSERT_TRUE(fabs(h0.geom_center().dist(Point(0, 0))) <= FLT_EPSILON);
    ASSERT_TRUE(fabs(h1.geom_center().dist(Point(2, 2))) <= FLT_EPSILON);
}

// Tests for Octagon

TEST(octagon_test, default_constructor) {
    ASSERT_NO_THROW(Octagon());
}

TEST(octagon_test, point_constructor) {
    double R = 10 / (2 * sin(M_PI / 8));
    Point p1 = Point(R * std::cos(1 * 2 * M_PI / 8), R * std::sin(1 * 2 * M_PI / 8));
    Point p2 = Point(R * std::cos(2 * 2 * M_PI / 8), R * std::sin(2 * 2 * M_PI / 8));
    Point p3 = Point(R * std::cos(3 * 2 * M_PI / 8), R * std::sin(3 * 2 * M_PI / 8));
    Point p4 = Point(R * std::cos(4 * 2 * M_PI / 8), R * std::sin(4 * 2 * M_PI / 8));
    Point p5 = Point(R * std::cos(5 * 2 * M_PI / 8), R * std::sin(5 * 2 * M_PI / 8));
    Point p6 = Point(R * std::cos(6 * 2 * M_PI / 8), R * std::sin(6 * 2 * M_PI / 8));
    Point p7 = Point(R * std::cos(7 * 2 * M_PI / 8), R * std::sin(7 * 2 * M_PI / 8));
    Point p8 = Point(R * std::cos(8 * 2 * M_PI / 8), R * std::sin(8 * 2 * M_PI / 8));

    ASSERT_NO_THROW(Octagon(p1, p2, p3, p4, p5, p6, p7, p8));
    EXPECT_THROW(Octagon(Point(50.0, 50.0), p2, p3, p4, p5, p6, p7, p8), std::logic_error);
}

TEST(octagon_test, side_constructor) {
    ASSERT_NO_THROW(Octagon(8));
    EXPECT_THROW(Octagon(-15), std::logic_error);
}

TEST(octagon_test, equality) {
    double R = 10 / (2 * sin(M_PI / 8));
    Point p1 = Point(R * std::cos(1 * 2 * M_PI / 8), R * std::sin(1 * 2 * M_PI / 8));
    Point p2 = Point(R * std::cos(2 * 2 * M_PI / 8), R * std::sin(2 * 2 * M_PI / 8));
    Point p3 = Point(R * std::cos(3 * 2 * M_PI / 8), R * std::sin(3 * 2 * M_PI / 8));
    Point p4 = Point(R * std::cos(4 * 2 * M_PI / 8), R * std::sin(4 * 2 * M_PI / 8));
    Point p5 = Point(R * std::cos(5 * 2 * M_PI / 8), R * std::sin(5 * 2 * M_PI / 8));
    Point p6 = Point(R * std::cos(6 * 2 * M_PI / 8), R * std::sin(6 * 2 * M_PI / 8));
    Point p7 = Point(R * std::cos(7 * 2 * M_PI / 8), R * std::sin(7 * 2 * M_PI / 8));
    Point p8 = Point(R * std::cos(8 * 2 * M_PI / 8), R * std::sin(8 * 2 * M_PI / 8));
    Octagon o0(p1, p2, p3, p4, p5, p6, p7, p8);

    Octagon o1(p1, p2, p3, p4, p5, p6, p7, p8);
    Octagon o2(o1);
    Octagon o3(123);

    ASSERT_TRUE(o1 == o0);
    ASSERT_TRUE(o2 == o0);
    ASSERT_FALSE(o3 == o1);
}


TEST(octagon_test, area_test) {
    Octagon o0(3);

    ASSERT_TRUE(fabs(o0.area() - (2 * 3 * 3 * (sqrt(2) + 1))) <= FLT_EPSILON);
}

TEST(octagon_test, double_test) {
    Octagon o0(3);

    ASSERT_TRUE(fabs(static_cast<double>(o0) - (2 * 3 * 3 * (sqrt(2) + 1))) <= FLT_EPSILON);
}


TEST(octagon_test, geom_center) {
    Octagon o0(3);

    double R = 6;
    Point p1 = Point(R * std::cos(1 * 2 * M_PI / 8) + 11, R * std::sin(1 * 2 * M_PI / 8) + 3);
    Point p2 = Point(R * std::cos(2 * 2 * M_PI / 8) + 11, R * std::sin(2 * 2 * M_PI / 8) + 3);
    Point p3 = Point(R * std::cos(3 * 2 * M_PI / 8) + 11, R * std::sin(3 * 2 * M_PI / 8) + 3);
    Point p4 = Point(R * std::cos(4 * 2 * M_PI / 8) + 11, R * std::sin(4 * 2 * M_PI / 8) + 3);
    Point p5 = Point(R * std::cos(5 * 2 * M_PI / 8) + 11, R * std::sin(5 * 2 * M_PI / 8) + 3);
    Point p6 = Point(R * std::cos(6 * 2 * M_PI / 8) + 11, R * std::sin(6 * 2 * M_PI / 8) + 3);
    Point p7 = Point(R * std::cos(7 * 2 * M_PI / 8) + 11, R * std::sin(7 * 2 * M_PI / 8) + 3);
    Point p8 = Point(R * std::cos(8 * 2 * M_PI / 8) + 11, R * std::sin(8 * 2 * M_PI / 8) + 3);
    Octagon o1(p1, p2, p3, p4, p5, p6, p7, p8);

    ASSERT_TRUE(fabs(o0.geom_center().dist(Point(0, 0))) <= FLT_EPSILON);
    ASSERT_TRUE(fabs(o1.geom_center().dist(Point(11, 3))) <= FLT_EPSILON);
}

// Test for Vector

TEST(vector_test, constructor_default_vector) {
    bool test = true;
    try {
        Vector<int64_t> a;
    }
    catch (std::range_error &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        test = false;
    }

    ASSERT_TRUE(test);
    Vector<int64_t> a;
    ASSERT_TRUE(a.empty());
    ASSERT_TRUE(a.capacity() == 1);
}

TEST(vector_test, constructor_initializer_list) {
    bool test = true;
    try {
        Vector<char> o{'5', '1', '0', '3'};
    }
    catch (std::range_error &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        test = false;
    }
    ASSERT_TRUE(test);
    Vector<char> o{'5', '1', '0', '3'};
    ASSERT_TRUE(o.size() == 4);
}

TEST(vector_test, reserve) {
    Vector<int64_t> test_1;
    size_t capacity = 1000;

    test_1.reserve(capacity);

    ASSERT_TRUE(test_1.capacity() == capacity);
}

TEST(vector_test, test_equality) {
    Vector<char> o1{'0', '5', '1'};
    Vector<char> o2{'0', '5', '1'};
    Vector<char> o3{'0', '5', '1', '4'};
    Vector<char> o4{'2', '5', '1'};
    ASSERT_TRUE(o1 == o1);
    ASSERT_TRUE(o1 == o2);
    ASSERT_FALSE(o1 == o3);
    ASSERT_FALSE(o1 == o4);
}

TEST(vector_test, test_not_equality) {
    Vector<char> o1{'0', '5', '1'};
    Vector<char> o2{'0', '5', '1'};
    Vector<char> o3{'0', '5', '1', '4'};
    Vector<char> o4{'2', '5', '1'};
    ASSERT_FALSE(o1 != o1);
    ASSERT_FALSE(o1 != o2);
    ASSERT_TRUE(o1 != o3);
    ASSERT_TRUE(o1 != o4);
}

TEST(vector_test, constructor_copy) {
    bool test = true;
    Vector<char> o1{'5', '1', '0', '3'};
    try {
        Vector<char> o(o1);
    }
    catch (std::range_error &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        test = false;
    }
    ASSERT_TRUE(test);
    Vector<char> o(o1);
    ASSERT_TRUE(o == o1);
}

TEST(vector_test, test_operator_squarebracket) {
    Vector<char> o1{'5', '1', '0', '3'};
    ASSERT_TRUE(o1[2] == '0');
    ASSERT_TRUE(o1[1] == '1');
    ASSERT_TRUE(o1[0] == '5');
    ASSERT_TRUE(o1[3] == '3');
    o1[3] = '8';
    ASSERT_TRUE(o1[3] == '8');
}

TEST(vector_test, const_test_operator_squarebracket) {
    const Vector<char> o1{'5', '1', '0', '3'};
    ASSERT_TRUE(o1[2] == '0');
    ASSERT_TRUE(o1[1] == '1');
    ASSERT_TRUE(o1[0] == '5');
    ASSERT_TRUE(o1[3] == '3');
}

TEST(vector_test, push_back) {
    Vector<int> a;
    Vector<int> a1{1};
    Vector<int> a2{1, 2, 3};
    a.push_back(1);
    ASSERT_TRUE(a1 == a);
    a.push_back(2);
    a.push_back(3);
    ASSERT_TRUE(a2 == a);
}

TEST(vector_test, pop_back) {
    Vector<int> a;
    Vector<int> a1{1};
    Vector<int> a2{1, 2, 3};
    a2.pop_back();
    a2.pop_back();
    ASSERT_TRUE(a1 == a2);
    a2.pop_back();
    ASSERT_TRUE(a2 == a);
}

TEST(vector_test, const_test_erase) {
    Vector<char> o1{'5', '1', '0', '3'};
    Vector<char> o2{'5', '0', '3'};
    Vector<char> o3{'5', '0'};
    bool test = false;
    try {
        o1.erase(5);
    } catch (std::out_of_range &ex) {
        test = true;
    }
    ASSERT_TRUE(test);
    o1.erase(1);
    ASSERT_TRUE(o1 == o2);
    o1.erase(2);
    ASSERT_TRUE(o1 == o3);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
