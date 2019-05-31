//
// Created by Drasik on 5/30/2019.
//

#ifndef SO2_EMPLOYEE_H
#define SO2_EMPLOYEE_H

#include <thread>
#include "./Office/Office.h"

class Employee : DisplayConnector {
    using DisplayConnector::DisplayConnector;
    static int living;
private:
    Office *office;
    std::string index;
    std::thread life_thread;
    int crying_time = 200;  // 2 to 7 seconds
    int meeting_time = 5000 + rand() % 10000;  // 2 to 7 seconds
    int coffee_time = 5000 + rand() % 5000;  // 2 to 4 seconds
    int work_time = 5000 + rand() % 15000;  // 2 to 12 seconds
public:
    void assign_to_office(Office *office);
    void born(int index);
    void live();
    static void stop_all();
    void kill();
};


#endif //SO2_EMPLOYEE_H
