#include <iostream>
#include "TurkishNumber.h"

int main() {
    std::cout << "Laba 1: Turkish number 0-99\n";
    std::cout << "Enter integer 0-99: ";
    int n;
    if (!(std::cin >> n)) {
        std::cerr << "Input error\n";
        return 1;
    }
    try {
        std::string name = number_to_turkish(n);
        std::cout << name << '\n';
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        return 1;
    }
    return 0;
}
