//
// Created by Drasik on 5/28/2019.
//

#include "Display.h"
#include <ncurses.h>
#include <string>
#include <iostream>
#include "./Office/Office.h"

Display::Display(bool ncurses_mode) {
    this->ncurses_mode = ncurses_mode;
}


void Display::start() {
    if (this->ncurses_mode) {
        initscr();
        std::string message = "hey";
        mvprintw(1, 0, message.c_str());    /* Print Hello World		  */
        refresh();            /* Print it on to the real screen */
    }
}

void Display::print(const std::string str){
    if (!this->ncurses_mode) {
        this->cout_mutex.lock();
        std::cout << str << std::endl;
        this->cout_mutex.unlock();
    }
}
