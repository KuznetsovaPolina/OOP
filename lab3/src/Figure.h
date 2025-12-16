#pragma once
#include <iostream>
#include "Point.h"

class Figure {
public:
    virtual ~Figure() = default;

    virtual Point center() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Figure& f) {
    f.print(os);
    return os;
}
