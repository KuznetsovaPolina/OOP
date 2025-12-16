#include "FigureArray.h"
#include <stdexcept>

FigureArray::FigureArray() : data_(nullptr), size_(0), capacity_(0) {}

FigureArray::~FigureArray() {
    for (std::size_t i = 0; i < size_; ++i) {
        delete data_[i];
    }
    delete[] data_;
}

void FigureArray::reserve(std::size_t new_cap) {
    if (new_cap <= capacity_) return;
    Figure** new_data = new Figure*[new_cap];
    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
}

void FigureArray::push_back(Figure* f) {
    if (size_ == capacity_) {
        reserve(capacity_ == 0 ? 4 : capacity_ * 2);
    }
    data_[size_++] = f;
}

void FigureArray::remove_at(std::size_t idx) {
    if (idx >= size_) {
        throw std::out_of_range("Index out of range");
    }
    delete data_[idx];
    for (std::size_t i = idx + 1; i < size_; ++i) {
        data_[i - 1] = data_[i];
    }
    --size_;
}

Figure* FigureArray::operator[](std::size_t idx) const {
    if (idx >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[idx];
}
