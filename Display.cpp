//
// Created by Drasik on 5/28/2019.
//

#include "Display.h"
#include <ncurses.h>
#include <string>
#include <iostream>

Display::Display(bool ncurses_mode) {
    this->ncurses_mode = ncurses_mode;
}

std::string COVER = "        ";

void Display::start() {
    if (this->ncurses_mode) {
        initscr();
    }
}

void Display::print(const std::string str){
    if (!this->ncurses_mode) {
        this->cout_mutex.lock();
        std::cout << str << std::endl;
        this->cout_mutex.unlock();
    }
}

void Display::stop() {
    if (this->ncurses_mode) {
        endwin();
    }
}

void Display::update_desks(int delta) {
//    ncurses_mutex.lock();
    this->resources_used.desks += delta;
    int row = this->resource_lines.desks;
    std::string message = "Desks:\t" + std::to_string(this->resources_used.desks) + "/" + std::to_string(this->total_resources.desks) + COVER;
//    mvprintw(row, 0, message.c_str());
    this->row_messages[row] = message;
//    refresh();
//    ncurses_mutex.unlock();
}

void Display::set_total_desks(int number_of_desks) {
    this->total_resources.desks = number_of_desks;
}

void Display::set_meeting_room_size(int size) {
    this->meeting_room_sizes.push_back(size);
    this->meeting_room_usages.push_back(0);
}

void Display::update_cups_and_spons(int delta) {
//    ncurses_mutex.lock();
    this->resources_used.cups_and_spoons += delta;
    int row = this->resource_lines.cups_and_spoons;
    std::string message = "Cups/spoons:\t" + std::to_string(this->resources_used.cups_and_spoons) + "/" + std::to_string(this->total_resources.cups_and_spoons) + COVER;
    this->row_messages[row] = message;
    //    mvprintw(row, 0, message.c_str());
//    refresh();
//    ncurses_mutex.unlock();
}

void Display::set_total_cups_and_spoons(int number_of_spoons) {
    this->total_resources.cups_and_spoons = number_of_spoons;
}

void Display::update_meeting_room(int index, int delta) {
//    ncurses_mutex.lock();
    this->meeting_room_usages[index] += delta;
    int row = this->resource_lines.meeting_rooms + index;
    std::string message = "Meeting room:\t" + std::to_string(this->meeting_room_usages[index]) + "/" + std::to_string(this->meeting_room_sizes[index]) + COVER;
    this->row_messages[row] = message;
    //    mvprintw(row, 0, message.c_str());
//    refresh();
//    ncurses_mutex.unlock();
}

void Display::update_employee(int index, std::string status, int progress) {
    ncurses_mutex.lock();
    int row = this->resource_lines.meeting_rooms + this->meeting_room_sizes.size() + index;
    std::string progress_string;
    if (progress == -1) {
        progress_string = "";
    } else {
        progress_string = std::to_string(progress) + "%%";
    }
    std::string message = "Employee: " + std::to_string(index) +"\t" + status + "\t" + progress_string + COVER;
    mvprintw(row, 0, message.c_str());
    for(auto& row_message : row_messages)
    {
        mvprintw(row_message.first, 0, row_message.second.c_str());
    }
    refresh();
    ncurses_mutex.unlock();
}
