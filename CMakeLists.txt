cmake_minimum_required(VERSION 3.12)
project(Homework1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Homework1 main.cpp DataStorage.cpp DataStorage.h DrawManager.cpp DrawManager.h EventManager.cpp EventManager.h)

find_library(SYSTEM sfml-system)
find_library(WINDOW sfml-window)
find_library(GRAPHICS sfml-graphics)

target_link_libraries(Homework1 ${SYSTEM})
target_link_libraries(Homework1 ${WINDOW})
target_link_libraries(Homework1 ${GRAPHICS})