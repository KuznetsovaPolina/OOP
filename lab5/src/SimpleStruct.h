#pragma once
#include <string>
#include <ostream>

struct Person {
    std::string name;
    int age{};
    double salary{};
};

inline std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "Person{name='" << p.name << "', age=" << p.age << ", salary=" << p.salary << "}";
    return os;
}

inline bool operator==(const Person& a, const Person& b) {
    return a.name == b.name && a.age == b.age && a.salary == b.salary;
}
