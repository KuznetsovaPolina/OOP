#include <iostream>
#include <memory_resource>
#include "VectorMemoryResource.h"
#include "PmrQueue.h"
#include "SimpleStruct.h"

int main() {
    std::cout << "Lab 5: Iterators & Allocators (PMR queue)\n";

    VectorMemoryResource mem_res;
    std::pmr::polymorphic_allocator<std::byte> byte_alloc(&mem_res);
    (void)byte_alloc;

    PmrQueue<int> qi(&mem_res);
    qi.push(10);
    qi.push(20);
    qi.push(30);

    std::cout << "Queue<int>: ";
    for (auto& x : qi) {
        std::cout << x << " ";
    }
    std::cout << "\nFront = " << qi.front() << ", Back = " << qi.back() << "\n";

    qi.pop();
    std::cout << "After pop, Queue<int>: ";
    for (auto& x : qi) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    PmrQueue<Person> qp(&mem_res);
    qp.push(Person{"Alice", 30, 100000.0});
    qp.push(Person{"Bob", 25, 80000.0});

    std::cout << "\nQueue<Person>:\n";
    for (auto& p : qp) {
        std::cout << "  " << p << "\n";
    }

    std::cout << "\nProgram finished. All memory will be released by VectorMemoryResource destructor.\n";
    return 0;
}
