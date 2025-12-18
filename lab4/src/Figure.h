#pragma once
#include <ostream>
#include "Point.h"
template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    virtual Point<T> center() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream&) const = 0;
    explicit operator double() const { return area(); }
    bool operator==(const Figure& o) const { return area() == o.area(); }
};
template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& f) {
    f.print(os); return os;
}
