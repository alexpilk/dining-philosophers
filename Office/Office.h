//
// Created by Drasik on 5/30/2019.
//

#ifndef SO2_OFFICE_H
#define SO2_OFFICE_H

#include <vector>
#include <DisplayConnector.h>
#include "./Office/Rooms/Kitchen.h"
#include "./Office/Rooms/MeetingRoom.h"
#include "Desk.h"

class Office : DisplayConnector {
    using DisplayConnector::DisplayConnector;
private:
    std::vector<Desk *> desks;
    std::vector<MeetingRoom *> meeting_rooms;
    Kitchen *kitchen;
public:
    void generate_desks(int number_of_desks);

    void generate_meeting_rooms(std::vector<int> meeting_room_sizes);

    void add_kitchen(Kitchen *kitchen);

    bool request_desk(int duration, std::string);

    bool request_coffee(int duration, std::string);

    bool request_meeting(int duration, std::string);

    void wait(int duration, std::string index, std::string status);
};


#endif //SO2_OFFICE_H
