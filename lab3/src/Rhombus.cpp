#include "Rhombus.h"
#include "QuadUtils.h"

Rhombus::Rhombus(const Point& a, const Point& b, const Point& c, const Point& d) {
    v_[0] = a;
    v_[1] = b;
    v_[2] = c;
    v_[3] = d;
}

bool Rhombus::operator==(const Rhombus& other) const {
    for (int i = 0; i < 4; ++i) {
        if (v_[i].x != other.v_[i].x || v_[i].y != other.v_[i].y) return false;
    }
    return true;
}

Point Rhombus::center() const {
    return quad_center(v_);
}

double Rhombus::area() const {
    return quad_area(v_);
}

void Rhombus::print(std::ostream& os) const {
    os << "Rhombus: ";
    for (int i = 0; i < 4; ++i) {
        os << "(" << v_[i].x << ", " << v_[i].y << ") ";
    }
}

std::istream& operator>>(std::istream& is, Rhombus& r) {
    for (int i = 0; i < 4; ++i) {
        is >> r.v_[i].x >> r.v_[i].y;
    }
    return is;
}
