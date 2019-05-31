//
// Created by pilkevyc on 2019-05-31.
//

#include "EmployeeManager.h"


void EmployeeManager::assign_to_office(Office *office) {
    this->office = office;
}

Employee *EmployeeManager::create_employee() {
    auto* employee = new Employee(this->display);
    employee->assign_to_office(office);
    int employee_index = this->employees.size();
    employee->born(employee_index);
    this->employees.push_back(employee);
    return employee;
}

void EmployeeManager::kill_employees() {
    Employee::stop_all();
    for (Employee* employee : this->employees) {
        employee->kill();
    }
}
