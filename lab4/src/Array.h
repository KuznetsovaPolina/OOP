#pragma once
#include <memory>
#include <utility>
#include <stdexcept>
template<class T>
class Array {
    std::shared_ptr<T[]> d;
    size_t sz=0,cap=0;
    void grow(){
        size_t nc=cap?cap*2:4;
        auto nd=std::shared_ptr<T[]>(new T[nc]);
        for(size_t i=0;i<sz;i++) nd[i]=std::move(d[i]);
        d=nd; cap=nc;
    }
public:
    void push_back(T v){ if(sz==cap)grow(); d[sz++]=std::move(v); }
    void remove_at(size_t i){
        if(i>=sz)throw std::out_of_range("idx");
        for(size_t j=i+1;j<sz;j++) d[j-1]=std::move(d[j]);
        sz--;
    }
    size_t size() const{return sz;}
    T& operator[](size_t i){return d[i];}
    const T& operator[](size_t i)const{return d[i];}
};
