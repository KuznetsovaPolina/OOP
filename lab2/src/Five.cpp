#include "Five.h"
#include <stdexcept>

void Five::check_digit(unsigned char d) const {
    if (d > 4) throw std::invalid_argument("Digit must be 0..4");
}

Five::Five() : size_(1), data_(new unsigned char[1]{0}) {}

Five::Five(size_t n, unsigned char fill) : size_(n) {
    check_digit(fill);
    data_ = new unsigned char[n];
    for(size_t i=0;i<n;i++) data_[i]=fill;
}

Five::Five(const std::initializer_list<unsigned char>& list)
: size_(list.size()) {
    data_ = new unsigned char[size_];
    size_t i=0;
    for(unsigned char d: list){
        check_digit(d);
        data_[i++]=d;
    }
}

Five::Five(const std::string& s){
    if(s.empty()) throw std::invalid_argument("Empty string");
    size_=s.size();
    data_=new unsigned char[size_];
    for(size_t i=0;i<size_;i++){
        char c=s[size_-1-i];
        if(c<'0'||c>'4') throw std::invalid_argument("Invalid digit");
        data_[i]=c-'0';
    }
}

Five::Five(const Five& other): size_(other.size_){
    data_=new unsigned char[size_];
    for(size_t i=0;i<size_;i++) data_[i]=other.data_[i];
}

Five::Five(Five&& other) noexcept
: size_(other.size_), data_(other.data_){
    other.data_=nullptr;
    other.size_=0;
}

Five::~Five() noexcept{
    delete[] data_;
}

size_t Five::size() const {return size_;}

unsigned char Five::digit(size_t index) const{
    if(index>=size_) throw std::out_of_range("Index out of range");
    return data_[index];
}

std::string Five::to_string() const{
    std::string s;
    s.reserve(size_);
    for(size_t i=0;i<size_;i++)
        s.insert(s.begin(), char('0'+data_[i]));
    return s;
}

Five Five::copy() const { return Five(*this); }

Five Five::add(const Five& other) const{
    size_t n = (size_>other.size_? size_:other.size_);
    unsigned char* res=new unsigned char[n+1];
    unsigned char carry=0;
    size_t i=0;
    for(;i<n;i++){
        unsigned char a = (i<size_? data_[i]:0);
        unsigned char b = (i<other.size_? other.data_[i]:0);
        unsigned char sum = a+b+carry;
        res[i]=sum%5;
        carry=sum/5;
    }
    if(carry){
        res[n]=carry;
        Five r;
        delete[] r.data_;
        r.size_=n+1;
        r.data_=res;
        return r;
    } else {
        Five r;
        delete[] r.data_;
        r.size_=n;
        r.data_=new unsigned char[n];
        for(size_t j=0;j<n;j++) r.data_[j]=res[j];
        delete[] res;
        return r;
    }
}

Five Five::sub(const Five& other) const{
    if(other.greater(*this)) throw std::runtime_error("Negative result");
    size_t n=size_;
    unsigned char* res=new unsigned char[n];
    unsigned char borrow=0;
    for(size_t i=0;i<n;i++){
        int a=data_[i];
        int b=(i<other.size_? other.data_[i]:0);
        int v=a-b-borrow;
        if(v<0){ v+=5; borrow=1;} else borrow=0;
        res[i]=v;
    }
    size_t newsize=n;
    while(newsize>1 && res[newsize-1]==0) newsize--;
    Five r;
    delete[] r.data_;
    r.size_=newsize;
    r.data_=new unsigned char[newsize];
    for(size_t i=0;i<newsize;i++) r.data_[i]=res[i];
    delete[] res;
    return r;
}

bool Five::equals(const Five& other) const{
    if(size_!=other.size_) return false;
    for(size_t i=0;i<size_;i++)
        if(data_[i]!=other.data_[i]) return false;
    return true;
}

bool Five::less(const Five& other) const{
    if(size_!=other.size_) return size_<other.size_;
    for(size_t i=size_; i-- >0; ){
        if(data_[i]!=other.data_[i])
            return data_[i]<other.data_[i];
    }
    return false;
}

bool Five::greater(const Five& other) const{
    return other.less(*this);
}
