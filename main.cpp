#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <ncurses.h>
#include <vector>
#include "Display.h"
#include "Employee.h"
#include "./Office/Office.h"
#include "./Office/Rooms/Kitchen.h"
#include "EmployeeManager.h"

void wait_for_exit() {
    while (true) {
        std::string key;
        key = std::cin.get();
        if (key == "e") {
            break;
        }
    }
}

int NUMBER_OF_EMPLOYEES = 20;

int main(int argc, char **argv) {
    auto *display = new Display(true);

    auto *kitchen = new Kitchen(display);
    kitchen->generate_cups_and_spoons(2);

    auto *office = new Office(display);
    std::vector<int> meeting_room_sizes = {2, 3};
    office->generate_meeting_rooms(meeting_room_sizes);
    office->generate_desks(3);
    office->add_kitchen(kitchen);

    auto *employee_manager = new EmployeeManager(display);
    employee_manager->assign_to_office(office);

    for (int i = 0; i < NUMBER_OF_EMPLOYEES; i++) {
        employee_manager->create_employee();
    }

    display->start();

    wait_for_exit();

    employee_manager->kill_employees();
    display->stop();

    return 0;
}