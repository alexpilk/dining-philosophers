cmake_minimum_required(VERSION 3.9)
project(so2)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_COMPILER "/usr/bin/g++-8")
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_FLAGS "-lncurses")
#set(CMAKE_C_STANDARD "${CMAKE_C_FLAGS} -Wall -Werror -lpdcurses")
include_directories(./)
#include_directories(/usr/include/c++/8/)
set(SOURCE_FILES main.cpp Display.cpp Display.h ncurses.h)
add_executable(so2 main.cpp Display.cpp Display.h Office/Office.cpp Office/Office.h Office/Rooms/Kitchen.cpp Office/Rooms/Kitchen.h Office/Rooms/KitchenItems/Cup.cpp Office/Rooms/KitchenItems/Cup.h Office/Rooms/KitchenItems/Spoon.cpp Office/Rooms/KitchenItems/Spoon.h Office/Rooms/MeetingRoom.cpp Office/Rooms/MeetingRoom.h Employee.cpp Employee.h)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} curses)


