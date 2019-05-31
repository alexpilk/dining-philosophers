//
// Created by pilkevyc on 2019-05-31.
//

#ifndef SO2_DISPLAYCONNECTOR_H
#define SO2_DISPLAYCONNECTOR_H


#include "Display.h"

class DisplayConnector {
protected:
    Display* display;
public:
    explicit DisplayConnector(Display* display);
};


#endif //SO2_DISPLAYCONNECTOR_H
