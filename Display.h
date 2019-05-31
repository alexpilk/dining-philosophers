//
// Created by Drasik on 5/28/2019.
//

#ifndef SO2_DISPLAY_H
#define SO2_DISPLAY_H

#include <string>
#include <mutex>
#include <vector>
#include <map>
// Desks
// Cups / Spoons
// Meeting room 1...

struct Resources {
    int desks;
    int cups_and_spoons;
    int meeting_rooms;
};

class Display {
private:
    bool ncurses_mode;
    std::mutex cout_mutex;
    std::mutex ncurses_mutex;
    Resources resource_lines = {0, 1, 2};
    Resources total_resources;
    Resources resources_used = {0, 0, 0};
    std::vector<int> meeting_room_sizes;
    std::vector<int> meeting_room_usages;
    std::map<int, std::string> row_messages;
public:
    explicit Display(bool ncurses_mode);
    void start();
    void stop();
    void update_desks(int delta);
    void set_total_desks(int number_of_desks);
    void update_meeting_room(int index, int delta);
    void set_meeting_room_size(int size);
    void update_cups_and_spons(int delta);
    void set_total_cups_and_spoons(int number_of_spoons);
    void update_employee(int index, std::string status, int progress);
    void print(std::string str);
};


#endif //SO2_DISPLAY_H
