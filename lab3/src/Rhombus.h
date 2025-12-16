#pragma once

#include "Figure.h"

class Rhombus : public Figure {
private:
    Point v_[4];

public:
    Rhombus() = default;
    Rhombus(const Point& a, const Point& b, const Point& c, const Point& d);

    Rhombus(const Rhombus&) = default;
    Rhombus(Rhombus&&) noexcept = default;
    Rhombus& operator=(const Rhombus&) = default;
    Rhombus& operator=(Rhombus&&) noexcept = default;

    bool operator==(const Rhombus& other) const;

    Point center() const override;
    double area() const override;
    void print(std::ostream& os) const override;

    explicit operator double() const { return area(); }

    const Point& vertex(size_t i) const { return v_[i]; }

    friend std::istream& operator>>(std::istream& is, Rhombus& r);
};
