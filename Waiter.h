//
// Created by Drasik on 4/7/2019.
//

#ifndef SO2_WAITER_H
#define SO2_WAITER_H

#include <vector>
#include <mutex>
class Philosopher;

#include "Fork.h"
#include "Philosopher.h"

class Waiter {
private:
    std::vector<Philosopher*> philosophers;
    std::vector<Fork*> forks;
    std::vector<Philosopher*> queue;
    bool force_request_forks(Philosopher* philosopher);
    void wait_in_queue(Philosopher* philosopher);

public:
    bool EXIT = false;
    Waiter(int philosophers);
    Philosopher* add_philosopher(int eating_time, int thinking_time);
    void request_forks(Philosopher* philosopher);
    void return_forks(Philosopher* philosopher);
    void add_to_queue(Philosopher* philosopher);
    bool is_queue_free(Philosopher* philosopher);
    void release_from_queue();
};


#endif //SO2_WAITER_H
