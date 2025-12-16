cmake_minimum_required(VERSION 3.20)
project(Lab1TurkishNumber)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(turkish_number
    src/TurkishNumber.cpp
)

target_include_directories(turkish_number PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE turkish_number)

enable_testing()
find_package(GTest REQUIRED)
add_executable(test_turkish tests/test_turkish.cpp)
target_link_libraries(test_turkish PRIVATE turkish_number GTest::GTest GTest::Main)
add_test(NAME TurkishNumberTests COMMAND test_turkish)
