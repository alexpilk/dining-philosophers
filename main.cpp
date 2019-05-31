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

void wait_for_exit()
{
    while (true) {
        std::string key;
        key = std::cin.get();
        if (key == "e") {
            break;
        }
    }
}


int main(int argc, char** argv)
{
    auto* kitchen = new Kitchen();
    kitchen->generate_cups(10);
    kitchen->generate_spoons(10);

    auto* office = new Office();
    std::vector meeting_room_sizes = {3, 5, 8};
    office->generate_meeting_rooms(meeting_room_sizes);
    office->add_kitchen(kitchen);

    for (int i =0; i < NUMBER_OF_EMPLOYEES; i++) {
        auto* employee = new Employee();
        office->add_employee(employee);
//        threads[i] = std::thread(&Philosopher::loop, p);
    }
    auto* display = new Display(false);

    display->start();
    display->print("dupa");

//    auto* waiter = new Waiter();
//
//    const int PHILOSOPHERS = 5;
////    int thinking_sleeping[PHILOSOPHERS][2] = {{200, 250}, {300, 300}, {400, 350}, {500, 100}, {600, 200}};
////    int thinking_sleeping[PHILOSOPHERS][2] = {{2000, 2000}, {2000, 2000}, {2000, 2000}, {2000, 2000}, {2000, 2000}};
//    int thinking_sleeping[PHILOSOPHERS][2] = {{8000, 8000}, {5000, 6000}, {2000, 3000}, {2000, 2000}, {7000, 6000}};
//    std::thread threads[PHILOSOPHERS];
//    for (int i =0; i < PHILOSOPHERS; i++) {
//        Philosopher* p = waiter->add_philosopher(thinking_sleeping[i][0], thinking_sleeping[i][1]);
//        threads[i] = std::thread(&Philosopher::loop, p);
//    }
//
//    initscr();			/* Start curses mode 		  */
//    std::thread w(&Waiter::release_from_queue, waiter);
    wait_for_exit();
    office->kill_employees();
    display->stop();
//    w.join();
//    for (auto &thread : threads) {
//        thread.join();
//    }
//    endwin();			/* End curses mode		  */
//
//    return 0;
}