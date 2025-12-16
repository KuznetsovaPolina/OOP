#pragma once

#include "Figure.h"

class Rectangle : public Figure {
private:
    Point v_[4];

public:
    Rectangle() = default;
    Rectangle(const Point& a, const Point& b, const Point& c, const Point& d);

    Rectangle(const Rectangle&) = default;
    Rectangle(Rectangle&&) noexcept = default;
    Rectangle& operator=(const Rectangle&) = default;
    Rectangle& operator=(Rectangle&&) noexcept = default;

    bool operator==(const Rectangle& other) const;

    Point center() const override;
    double area() const override;
    void print(std::ostream& os) const override;

    explicit operator double() const { return area(); }

    const Point& vertex(size_t i) const { return v_[i]; }

    friend std::istream& operator>>(std::istream& is, Rectangle& r);
};
