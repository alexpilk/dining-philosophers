//
// Created by Drasik on 4/7/2019.
//

#include "Waiter.h"
#include <thread>
#include <iostream>

//bool EXIT_F;
std::mutex my_mutex;
std::mutex queue_mutex;
std::mutex release_mutex;

bool release_alert = false;
bool got_retry_alert = false;

bool Waiter::force_request_forks(Philosopher *philosopher) {
    int id = philosopher->get_id();
    //std::cout << "Philosopher " << id << " requesting forks..." << std::endl;
    my_mutex.lock();
    //std::cout << "Philosopher " << id << " granted request attempt" << std::endl;
    int L = id;
    int R = id == this->forks.size() - 1 ? 0 : L + 1;
    if(this->forks[L]->mutex.try_lock()) {
        //std::cout << "Philosopher " << id << " got L " << L << std::endl;
        if(this->forks[R]->mutex.try_lock()) {
            //std::cout << "Philosopher " << id << " got R " << R  << std::endl;
            my_mutex.unlock();
            return true;
        } else {
            //std::cout << "No R " << R << std::endl;
            this->forks[L]->mutex.unlock();
            my_mutex.unlock();
            return false;
        }
    } else {
        //std::cout << "No L " << L << std::endl;
        my_mutex.unlock();
        return false;
    }
}


void Waiter::request_forks(Philosopher* philosopher) {
    release_mutex.lock();
    if(this->is_queue_free(philosopher)) {
        if(this->force_request_forks(philosopher)) {
            release_mutex.unlock();
            return;
        }
    }
    release_mutex.unlock();
    this->add_to_queue(philosopher);
    this->wait_in_queue(philosopher);
}


void Waiter::return_forks(Philosopher* philosopher) {
    int id = philosopher->get_id();
    int L = id;
    int R = id == this->forks.size() - 1 ? 0 : L + 1;
    this->forks[L]->mutex.unlock();
    //std::cout << "Philosopher " << id << " returned L " << L << std::endl;
    this->forks[R]->mutex.unlock();
    //std::cout << "Philosopher " << id << " returned R " << R << std::endl;
    release_alert = true;
}

Philosopher* Waiter::add_philosopher(int eating_time, int thinking_time) {
    auto* philosopher = new Philosopher(this, (int)this->philosophers.size(), eating_time, thinking_time);
    this->philosophers.push_back(philosopher);
    Fork* fork = new Fork();
    this->forks.push_back(fork);
    return philosopher;
}


void Waiter::add_to_queue(Philosopher *philosopher) {
    this->queue.push_back(philosopher);
    //std::cout << "Philosopher " << philosopher->get_id() << " added to queue" << std::endl;
}

void Waiter::wait_in_queue(Philosopher *philosopher) {
    //std::cout << "Philosopher " << philosopher->get_id() << " waiting in queue" << std::endl;
    while(!philosopher->retry) {}
    queue_mutex.lock();
    got_retry_alert = true;
    //std::cout << "Trying to release philosopher " << philosopher->get_id() << " from queue" << std::endl;
    philosopher->retry = false;
    if(this->force_request_forks(philosopher)){
        //std::cout << "Philosopher " << philosopher->get_id() << " released from queue" << std::endl;
        int i = 0;
        for(; i < this->queue.size(); i++) {
            if (this->queue[i]->get_id() == philosopher->get_id()) {
                break;
            }
        }
        this->queue.erase(this->queue.begin()+i);
        //std::cout << "Philosopher " << philosopher->get_id() << " removed from queue" << std::endl;
        queue_mutex.unlock();
    } else {
        //std::cout << "Philosopher " << philosopher->get_id() << " remains in queue" << std::endl;
        queue_mutex.unlock();
        wait_in_queue(philosopher);
    }
}

bool Waiter::is_queue_free(Philosopher *philosopher) {
    int id = philosopher->get_id();
    int L_id = id == 0 ? this->queue.size() - 1 : id - 1;
    int R_id = id == this->queue.size() - 1 ? 0 : id + 1;
    for(Philosopher* p : this->queue) {
        int p_id = p->get_id();
        if (p_id == L_id || p_id == R_id) {
            //std::cout << "Queue isn't free for philosopher " << id << std::endl;
            return false;
        }
    }
    //std::cout << "Queue is free for philosopher " << id << std::endl;
    return true;
}

void Waiter::release_from_queue() {
    //std::cout << "Waiter is monitoring the queue..." << std::endl;
    while(!release_alert) {
        if(this->queue.empty() && this->EXIT) {
            return;
        }
    }
    release_alert = false;
    //std::cout << "Queue release engaged!" << std::endl;
    release_mutex.lock();
    //std::cout << "Queue release started!" << std::endl;
    std::vector<Philosopher*> queue_copy(this->queue);
    queue_mutex.lock();
    for(Philosopher* p : queue_copy) {
        queue_mutex.unlock();
        p->retry=true;
        while(!got_retry_alert) {}
        got_retry_alert = false;
        queue_mutex.lock();
    }
    queue_mutex.unlock();
    release_mutex.unlock();
    release_from_queue();
}
