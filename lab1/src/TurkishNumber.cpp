#include "TurkishNumber.h"
#include <stdexcept>

std::string number_to_turkish(int n) {
    if (n < 0 || n > 99) {
        throw std::out_of_range("number_to_turkish: n must be in [0, 99]");
    }

    static const char* units[] = {
        "sıfır",
        "bir",
        "iki",
        "üç",
        "dört",
        "beş",
        "altı",
        "yedi",
        "sekiz",
        "dokuz"
    };

    static const char* tens[] = {
        "",
        "on",
        "yirmi",
        "otuz",
        "kırk",
        "elli",
        "altmış",
        "yetmiş",
        "seksen",
        "doksan"
    };

    if (n < 10) {
        return units[n];
    }

    int t = n / 10;
    int u = n % 10;

    if (u == 0) {
        return tens[t];
    }

    std::string result = tens[t];
    result += ' ';
    result += units[u];
    return result;
}
