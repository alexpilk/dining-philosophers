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
        this->display->set_meeting_room_size(size);
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
    this->display->set_total_desks(number_of_desks);
}

bool Office::request_desk(int duration, std::string index) {
    this->display->print("Employee " + index + " requested a desk...");
    for (Desk* desk : this->desks) {
        bool locked = desk->mutex.try_lock();
        if  (locked) {
            this->display->update_desks(1);
            this->display->print("Employee " + index + " locked a desk...");
            this->wait(duration, index, "WORKING   ");
            desk->mutex.unlock();
            this->display->update_desks(-1);
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
        this->display->update_cups_and_spons(1);
        this->display->print("Employee " + index + " started drinking coffee");
        this->wait(duration, index, "COFFEE   ");
        this->kitchen->return_cup_and_spoon(cup_spoon_pair);
        this->display->update_cups_and_spons(-1);
        this->display->print("Employee " + index + " stopped drinking coffee");
        return true;
    }
    this->display->print("Employee " + index + " can't drink coffee. No cups or spoons left.");
    return false;
}

bool Office::request_meeting(int duration, std::string index) {
    this->display->print("Employee " + index + " wants to join a meeting...");
    for (int i = 0; i < this->meeting_rooms.size(); i++) {
        MeetingRoom* room = this->meeting_rooms[i];
        bool entered = room->enter();
        if  (entered) {
            this->display->update_meeting_room(i, 1);
            this->display->print("Employee " + index + " joined a meeting");
            this->wait(duration, index, "MEETING_#" + std::to_string(i));
            room->exit();
            this->display->update_meeting_room(i, -1);
            this->display->print("Employee " + index + " left the meeting");
            return true;
        }
    }
    this->display->print("Employee " + index + " can't join any meeting. No rooms left.");
    return false;
}

void Office::wait(int duration, std::string index, std::string status) {
    int repetitions = duration / 100;
    for (int i = 0; i < repetitions; i++) {
        int progress = i*100/repetitions;
        this->display->update_employee(std::atoi(index.c_str()), status, progress);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
