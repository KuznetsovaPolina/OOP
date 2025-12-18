#pragma once
#include "Array.h"
template<class T>
double total_area(const Array<T>& a){
    double s=0; for(size_t i=0;i<a.size();i++) s+=static_cast<double>(*a[i]);
    return s;
}
