#pragma once
#include "PmrQueue.h"

template<class T>
T sum_queue(const PmrQueue<T>& q) {
    T acc{};
    for (auto& v : const_cast<PmrQueue<T>&>(q)) {
        acc += v;
    }
    return acc;
}
