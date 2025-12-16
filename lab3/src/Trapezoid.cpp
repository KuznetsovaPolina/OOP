#include "Trapezoid.h"
#include "QuadUtils.h"

Trapezoid::Trapezoid(const Point& a, const Point& b, const Point& c, const Point& d) {
    v_[0] = a;
    v_[1] = b;
    v_[2] = c;
    v_[3] = d;
}

bool Trapezoid::operator==(const Trapezoid& other) const {
    for (int i = 0; i < 4; ++i) {
        if (v_[i].x != other.v_[i].x || v_[i].y != other.v_[i].y) return false;
    }
    return true;
}

Point Trapezoid::center() const {
    return quad_center(v_);
}

double Trapezoid::area() const {
    return quad_area(v_);
}

void Trapezoid::print(std::ostream& os) const {
    os << "Trapezoid: ";
    for (int i = 0; i < 4; ++i) {
        os << "(" << v_[i].x << ", " << v_[i].y << ") ";
    }
}

std::istream& operator>>(std::istream& is, Trapezoid& t) {
    for (int i = 0; i < 4; ++i) {
        is >> t.v_[i].x >> t.v_[i].y;
    }
    return is;
}
