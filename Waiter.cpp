//
// Created by Drasik on 4/7/2019.
//

#include "Waiter.h"
#include <thread>
#include <iostream>
Waiter::Waiter(int philosophers) {
    for (int i = 0; i < philosophers; i++) {
        Fork* fork = new Fork();
        this->forks.push_back(fork);
    }
}

void Waiter::request_forks(Philosopher* philosopher) {
    int id = philosopher->get_id();
    int L = id;
    int R = id == this->forks.size() - 1 ? 0 : L + 1;
    std::cout << "(" << id << " " << L << " " << R << ")" << std::endl;
    if(this->forks[L]->mutex.try_lock()) {
        std::cout << "Got L " << L << std::endl;
        if(this->forks[R]->mutex.try_lock()) {
            std::cout << "Got R " << R  << std::endl;
            return;
        } else {
            std::cout << "No R " << R << std::endl;
            this->forks[L]->mutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(4000));
            return request_forks(philosopher);
        }
    } else {
        std::cout << "No L " << L << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(4000));
        return request_forks(philosopher);
    };
//    this->queue.push_back(philosopher);
}


void unlock(Fork* f){

    f->mutex.unlock();
}
void Waiter::return_forks(Philosopher* philosopher) {
    int L = philosopher->get_id();
    int R = L + 1;
    unlock(this->forks[L]);
    std::cout << "Returned L " << L << std::endl;
//    unlock(this->forks[R]);
//    this->forks[R]->mutex.unlock();
//    std::cout << "Returned R " << R << std::endl;
}
Philosopher* Waiter::add_philosopher(int eating_time, int thinking_time) {
    auto* philosopher = new Philosopher(this, (int)this->philosophers.size(), eating_time, thinking_time);
    this->philosophers.push_back(philosopher);
    return philosopher;
}
