cmake_minimum_required(VERSION 3.9)
project(so2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_FLAGS "-lncurses")
#set(CMAKE_C_STANDARD "${CMAKE_C_FLAGS} -Wall -Werror -lpdcurses")
include_directories(./)
set(SOURCE_FILES main.cpp Philosopher.cpp Philosopher.h Waiter.cpp Waiter.h ncurses.h)
add_executable(so2 main.cpp Philosopher.cpp Philosopher.h Waiter.cpp Waiter.h Status.h Fork.h)
target_link_libraries(${PROJECT_NAME} pthread)

