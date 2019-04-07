cmake_minimum_required(VERSION 3.9)
project(so2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(so2 main.cpp)