//
// Created by Drasik on 5/28/2019.
//

#ifndef SO2_DISPLAY_H
#define SO2_DISPLAY_H

#include <string>
#include <mutex>

class Display {
private:
    bool ncurses_mode;
    std::mutex cout_mutex;
public:
    explicit Display(bool ncurses_mode);
    void start();
    void stop();
    void print(std::string str);
};


#endif //SO2_DISPLAY_H
