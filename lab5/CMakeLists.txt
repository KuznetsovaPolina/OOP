cmake_minimum_required(VERSION 3.20)
project(Lab5IteratorsAllocators)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(pmr_queue
    src/VectorMemoryResource.h
    src/PmrQueue.h
    src/SimpleStruct.h
    src/TotalArea.h
)

target_include_directories(pmr_queue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE pmr_queue)

enable_testing()
find_package(GTest REQUIRED)
add_executable(test_queue tests/test_queue.cpp)
target_link_libraries(test_queue PRIVATE pmr_queue GTest::GTest GTest::Main)
add_test(NAME QueueTests COMMAND test_queue)
