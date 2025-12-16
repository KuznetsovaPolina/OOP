#pragma once

#include "Figure.h"

class Trapezoid : public Figure {
private:
    Point v_[4];

public:
    Trapezoid() = default;
    Trapezoid(const Point& a, const Point& b, const Point& c, const Point& d);

    Trapezoid(const Trapezoid&) = default;
    Trapezoid(Trapezoid&&) noexcept = default;
    Trapezoid& operator=(const Trapezoid&) = default;
    Trapezoid& operator=(Trapezoid&&) noexcept = default;

    bool operator==(const Trapezoid& other) const;

    Point center() const override;
    double area() const override;
    void print(std::ostream& os) const override;

    explicit operator double() const { return area(); }

    const Point& vertex(size_t i) const { return v_[i]; }

    friend std::istream& operator>>(std::istream& is, Trapezoid& t);
};
