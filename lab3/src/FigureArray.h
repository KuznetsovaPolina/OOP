#pragma once

#include <cstddef>
#include "Figure.h"

class FigureArray {
private:
    Figure** data_;
    std::size_t size_;
    std::size_t capacity_;

    void reserve(std::size_t new_cap);

public:
    FigureArray();
    ~FigureArray();

    FigureArray(const FigureArray&) = delete;
    FigureArray& operator=(const FigureArray&) = delete;

    std::size_t size() const { return size_; }

    void push_back(Figure* f);
    void remove_at(std::size_t idx);
    Figure* operator[](std::size_t idx) const;
};
