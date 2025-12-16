#pragma once

#include "Point.h"
#include <cmath>

inline double quad_area(const Point v[4]) {
    double sum = 0.0;
    for (int i = 0; i < 4; ++i) {
        int j = (i + 1) % 4;
        sum += v[i].x * v[j].y - v[j].x * v[i].y;
    }
    return 0.5 * std::abs(sum);
}

inline Point quad_center(const Point v[4]) {
    Point c{0.0, 0.0};
    for (int i = 0; i < 4; ++i) {
        c.x += v[i].x;
        c.y += v[i].y;
    }
    c.x /= 4.0;
    c.y /= 4.0;
    return c;
}
