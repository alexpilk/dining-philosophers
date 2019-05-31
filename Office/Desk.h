//
// Created by pilkevyc on 2019-05-31.
//

#ifndef SO2_DESK_H
#define SO2_DESK_H


#include <DisplayConnector.h>

class Desk : public DisplayConnector {
    using DisplayConnector::DisplayConnector;
public:
    std::mutex mutex;
};


#endif //SO2_DESK_H
