//
// Created by Drasik on 5/30/2019.
//

#include <thread>
#include "Office.h"

void Office::generate_meeting_rooms(std::vector<int> meeting_room_sizes) {
    for (int size : meeting_room_sizes) {
        auto *room = new MeetingRoom(this->display);
        room->set_size(size);
        this->meeting_rooms.push_back(room);
    }
}

void Office::add_kitchen(Kitchen *kitchen) {
    this->kitchen = kitchen;
}

void Office::generate_desks(int number_of_desks) {
    for (int i = 0; i < number_of_desks; i++) {
        auto *desk = new Desk(this->display);
        this->desks.push_back(desk);
    }
}

bool Office::request_desk(int duration, std::string index) {
    this->display->print("Employee " + index + " requested a desk...");
    for (Desk* desk : this->desks) {
        bool locked = desk->mutex.try_lock();
        if  (locked) {
            this->display->print("Employee " + index + " locked a desk...");
            this->wait(duration);
            desk->mutex.unlock();
            this->display->print("Employee " + index + " unlocked a desk...");
            return true;
        }
    }
    this->display->print("Employee " + index + " doesn't have a desk...");
    return false;
}


bool Office::request_coffee(int duration, std::string index) {
    this->display->print("Employee " + index + " wants coffee...");
    CupSpoonPair cup_spoon_pair = this->kitchen->take_cup_and_spoon();
    if  (cup_spoon_pair.cup != nullptr) {
        this->display->print("Employee " + index + " started drinking coffee");
        this->wait(duration);
        this->kitchen->return_cup_and_spoon(cup_spoon_pair);
        this->display->print("Employee " + index + " stopped drinking coffee");
        return true;
    }
    this->display->print("Employee " + index + " can't drink coffee. No cups or spoons left.");
    return false;
}

bool Office::request_meeting(int duration, std::string index) {
    this->display->print("Employee " + index + " wants to join a meeting...");
    for (MeetingRoom* room : this->meeting_rooms) {
        bool entered = room->enter();
        if  (entered) {
            this->display->print("Employee " + index + " joined a meeting");
            this->wait(duration);
            room->exit();
            this->display->print("Employee " + index + " left the meeting");
            return true;
        }
    }
    this->display->print("Employee " + index + " can't join any meeting. No rooms left.");
    return false;
}

void Office::wait(int duration) {
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}
