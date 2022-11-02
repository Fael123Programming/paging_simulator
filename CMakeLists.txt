cmake_minimum_required(VERSION 3.20)

project(Paging_Simulator)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE Paging_Simulator_SRC src/*.cpp)

add_executable(Paging_Simulator main.cpp ${Paging_Simulator_SRC})
