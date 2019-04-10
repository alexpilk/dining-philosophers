//
// Created by Drasik on 4/7/2019.
//
#include "Philosopher.h"
#include <thread>
#include <ncurses.h>
#include <mutex>


Philosopher::Philosopher(Waiter* waiter, int id, int eating_time, int thinking_time) {
    this->waiter = waiter;
    this->id = id;
    this->eating_time = eating_time;
    this->thinking_time = thinking_time;
//    this->status = UNDEFINED;
}

void Philosopher::eat() {
    this->waiter->request_forks(this);
    this->display("EATING", 5);
    std::this_thread::sleep_for(std::chrono::milliseconds(eating_time));
    this->waiter->return_forks(this);
}

void Philosopher::think() {
    this->display("THINKING", 5);
    std::this_thread::sleep_for(std::chrono::milliseconds(thinking_time));
    this->display("HUNGRY", 5);
}

void Philosopher::display(std::string status, int progress) {
//    std::string message = status + "\t" + std::to_string(progress);
//    mvprintw(this->id, 0, message.c_str());	/* Print Hello World		  */
//    refresh();			/* Print it on to the real screen */
}

void Philosopher::loop() {
    while (true) {
        this->think();
        this->eat();
    }
}

int Philosopher::get_id() {
    return this->id;
}

Status Philosopher::get_status() {
    return this->status;
}
