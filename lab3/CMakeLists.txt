cmake_minimum_required(VERSION 3.10)
project(Lab3Figures)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(figures
    src/Rectangle.cpp
    src/Trapezoid.cpp
    src/Rhombus.cpp
    src/FigureArray.cpp
    src/TotalArea.cpp
)

target_include_directories(figures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(main src/main.cpp)
target_link_libraries(main figures)

enable_testing()
find_package(GTest REQUIRED)
add_executable(test_figures tests/test_figures.cpp)
target_link_libraries(test_figures figures GTest::GTest GTest::Main)
add_test(NAME FiguresTests COMMAND test_figures)
