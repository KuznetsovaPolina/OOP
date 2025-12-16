cmake_minimum_required(VERSION 3.10)
project(FiveProject)
set(CMAKE_CXX_STANDARD 17)

add_library(five src/Five.cpp)
add_executable(main src/main.cpp)
target_link_libraries(main five)
