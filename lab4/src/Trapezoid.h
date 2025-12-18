#pragma once
#include "Figure.h"
#include <array>
#include <memory>
template<Scalar T>
class Trapezoid : public Figure<T> {
    std::array<std::unique_ptr<Point<T>>,4> p;
public:
    Trapezoid(){ for(auto&x:p)x=std::make_unique<Point<T>>(); }
    friend std::istream& operator>>(std::istream& is, Trapezoid& t){
        for(auto&x:t.p)is>>x->x>>x->y; return is;
    }
    Point<T> center() const override {
        T x{},y{}; for(auto&v:p){x+=v->x;y+=v->y;} return {x/4,y/4};
    }
    double area() const override {
        double a=std::abs(p[1]->x-p[0]->x);
        double b=std::abs(p[2]->x-p[3]->x);
        double h=std::abs(p[0]->y-p[2]->y);
        return (a+b)*h/2;
    }
    void print(std::ostream& os) const override {
        os<<"Trapezoid "; for(auto&v:p)os<<"("<<v->x<<","<<v->y<<") ";
    }
};
