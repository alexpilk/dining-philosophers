//
// Created by Drasik on 5/30/2019.
//

#include "Employee.h"

int Employee::living = true;

void Employee::assign_to_office(Office *office) {
    this->office = office;
}

void Employee::born(int index) {
    this->index = std::to_string(index);
    this->display->print("Gave birth to employee " + this->index);
    this->life_thread = std::thread(&Employee::live, this);
}

void Employee::live() {
    while(Employee::living) {
        bool desk = this->office->request_desk(this->work_time, this->index);
        bool coffee = this->office->request_coffee(this->coffee_time, this->index);
        bool meeting = this->office->request_meeting(this->meeting_time, this->index);
        if (!desk && !coffee && !meeting) {
            this->display->update_employee(std::atoi(this->index.c_str()), "¯\\_(*-*)_/¯   ", -1);
        }
    }
}

void Employee::kill() {
    this->life_thread.join();
    this->display->print("Killed employee " + this->index);
}

void Employee::stop_all() {
    Employee::living = false;
}
