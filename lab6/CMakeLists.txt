cmake_minimum_required(VERSION 3.20)
project(Lab6Patterns)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(core
    src/NPC.cpp
    src/Dragon.cpp
    src/Frog.cpp
    src/Knight.cpp
    src/NPCFactory.cpp
    src/Observer.cpp
    src/Battle.cpp
    src/Dungeon.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE core)

enable_testing()
find_package(GTest REQUIRED)
add_executable(test_battle tests/test_battle.cpp)
target_link_libraries(test_battle PRIVATE core GTest::GTest GTest::Main)
add_test(NAME BattleTests COMMAND test_battle)
