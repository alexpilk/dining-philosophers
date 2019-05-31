//
// Created by Drasik on 5/30/2019.
//

#include "MeetingRoom.h"

void MeetingRoom::set_size(int size) {
    this->size = size;
}

bool MeetingRoom::enter() {
    this->mutex.lock();
    if (this->people_inside >= size) {
        this->mutex.unlock();
        return false;
    } else {
        this->people_inside++;
        this->mutex.unlock();
        return true;
    }
}

void MeetingRoom::exit() {
    this->mutex.lock();
    this->people_inside--;
    this->mutex.unlock();
}
