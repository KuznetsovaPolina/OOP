#include <gtest/gtest.h>
#include "Rectangle.h"
#include "Trapezoid.h"
#include "Rhombus.h"
#include "FigureArray.h"
#include "TotalArea.h"

TEST(RectangleTest, AreaAndCenter) {
    Rectangle r({0,0}, {2,0}, {2,1}, {0,1});
    EXPECT_DOUBLE_EQ(r.area(), 2.0);
    Point c = r.center();
    EXPECT_DOUBLE_EQ(c.x, 1.0);
    EXPECT_DOUBLE_EQ(c.y, 0.5);
}

TEST(TrapezoidTest, AreaPositive) {
    Trapezoid t({0,0}, {3,0}, {2,1}, {0,1});
    EXPECT_GT(t.area(), 0.0);
}

TEST(RhombusTest, AreaAndCast) {
    Rhombus r({0,0}, {1,1}, {2,0}, {1,-1});
    double s1 = r.area();
    double s2 = static_cast<double>(r);
    EXPECT_DOUBLE_EQ(s1, s2);
}

TEST(FigureArrayTest, TotalArea) {
    FigureArray arr;
    arr.push_back(new Rectangle({0,0}, {1,0}, {1,1}, {0,1}));
    arr.push_back(new Rectangle({0,0}, {2,0}, {2,2}, {0,2}));
    double ta = total_area(arr);
    EXPECT_DOUBLE_EQ(ta, 5.0);
}
