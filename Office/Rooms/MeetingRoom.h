//
// Created by Drasik on 5/30/2019.
//

#ifndef SO2_MEETINGROOM_H
#define SO2_MEETINGROOM_H


#include <DisplayConnector.h>

class MeetingRoom: DisplayConnector {
    using DisplayConnector::DisplayConnector;
private:
    int size;
    int people_inside = 0;
    std::mutex mutex;
public:
    void set_size(int size);
    bool enter();
    void exit();
};


#endif //SO2_MEETINGROOM_H
