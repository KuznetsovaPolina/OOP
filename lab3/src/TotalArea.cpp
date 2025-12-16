#include "TotalArea.h"

double total_area(const FigureArray& arr) {
    double sum = 0.0;
    for (std::size_t i = 0; i < arr.size(); ++i) {
        sum += arr[i]->area();
    }
    return sum;
}
