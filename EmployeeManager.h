//
// Created by pilkevyc on 2019-05-31.
//

#ifndef SO2_EMPLOYEEMANAGER_H
#define SO2_EMPLOYEEMANAGER_H

#include <vector>
#include "Employee.h"

class EmployeeManager : DisplayConnector {
    using DisplayConnector::DisplayConnector;
private:
    Office *office;
    std::vector<Employee *> employees;
public:
    void assign_to_office(Office *office);

    Employee *create_employee();

    void kill_employees();
};


#endif //SO2_EMPLOYEEMANAGER_H
