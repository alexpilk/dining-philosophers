//
// Created by Drasik on 4/7/2019.
//

#ifndef SO2_PHILOSOPHER_H
#define SO2_PHILOSOPHER_H

class Waiter;

#include "Waiter.h"
#include "Status.h"
#include <string>


class Philosopher {
private:
    int id;
    int eating_time;
    int thinking_time;
    Status status;
    Waiter* waiter;

public:
    std::mutex mutex;
    Philosopher(Waiter* waiter, int id, int eating_time, int thinking_time);
    void think();
    void eat();
    void display(std::string status, int progress);
    void loop();
    int get_id();
    Status get_status();
};


#endif //SO2_PHILOSOPHER_H
