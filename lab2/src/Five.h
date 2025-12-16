#pragma once
#include <cstddef>
#include <string>
#include <initializer_list>

class Five {
private:
    size_t size_;
    unsigned char* data_;
    void check_digit(unsigned char d) const;

public:
    Five();
    Five(size_t n, unsigned char fill = 0);
    Five(const std::initializer_list<unsigned char>& list);
    Five(const std::string& digits);
    Five(const Five& other);
    Five(Five&& other) noexcept;
    ~Five() noexcept;

    size_t size() const;
    unsigned char digit(size_t index) const;

    Five add(const Five& other) const;
    Five sub(const Five& other) const;
    Five copy() const;

    bool equals(const Five& other) const;
    bool less(const Five& other) const;
    bool greater(const Five& other) const;

    std::string to_string() const;
};
