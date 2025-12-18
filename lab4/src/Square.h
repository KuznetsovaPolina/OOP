#pragma once
#include "Figure.h"
#include <array>
#include <memory>
template<Scalar T>
class Square : public Figure<T> {
    std::array<std::unique_ptr<Point<T>>,4> p;
public:
    Square(){ for(auto&x:p)x=std::make_unique<Point<T>>(); }
    friend std::istream& operator>>(std::istream& is, Square& s){
        for(auto&x:s.p)is>>x->x>>x->y; return is;
    }
    Point<T> center() const override {
        T x{},y{}; for(auto&v:p){x+=v->x;y+=v->y;} return {x/4,y/4};
    }
    double area() const override { return std::abs((p[1]->x-p[0]->x)*(p[2]->y-p[1]->y)); }
    void print(std::ostream& os) const override {
        os<<"Square "; for(auto&v:p)os<<"("<<v->x<<","<<v->y<<") ";
    }
};
