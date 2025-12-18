#include <gtest/gtest.h>
#include <memory>
#include "Square.h"
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Array.h"
#include "TotalArea.h"

TEST(SquareTest, AreaAndCenter) {
    using T = double;
    using P = Point<T>;
    Square<T> s(P{0,0}, P{1,0}, P{1,1}, P{0,1});
    EXPECT_DOUBLE_EQ(static_cast<double>(s), 1.0);
    auto c = s.center();
    EXPECT_DOUBLE_EQ(c.x, 0.5);
    EXPECT_DOUBLE_EQ(c.y, 0.5);
}

TEST(RectangleTest, Area) {
    using T = double;
    using P = Point<T>;
    Rectangle<T> r(P{0,0}, P{2,0}, P{2,1}, P{0,1});
    EXPECT_DOUBLE_EQ(static_cast<double>(r), 2.0);
}

TEST(TrapezoidTest, AreaPositive) {
    using T = double;
    using P = Point<T>;
    Trapezoid<T> t(P{0,0}, P{3,0}, P{2,1}, P{0,1});
    EXPECT_GT(static_cast<double>(t), 0.0);
}

TEST(ArrayTest, TotalArea) {
    using T = double;
    using F = Figure<T>;
    Array<std::shared_ptr<F>> arr;
    {
        auto s = std::make_shared<Square<T>>(Point<T>{0,0}, Point<T>{1,0}, Point<T>{1,1}, Point<T>{0,1});
        auto r = std::make_shared<Rectangle<T>>(Point<T>{0,0}, Point<T>{2,0}, Point<T>{2,2}, Point<T>{0,2});
        arr.push_back(s);
        arr.push_back(r);
    }
    double ta = total_area(arr);
    EXPECT_DOUBLE_EQ(ta, 1.0 + 4.0);
}
