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
    int concentration_time = 1000;
    void concentrate();
    void attempt_activity(bool (Office::*activity)(), std::string verbose_name);
public:
    void assign_to_office(Office *office);
    void born(int index);
    void live();
    static void stop_all();
    void kill();
};


#endif //SO2_EMPLOYEE_H
