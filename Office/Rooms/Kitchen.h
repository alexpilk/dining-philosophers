//
// Created by Drasik on 5/30/2019.
//

#ifndef SO2_KITCHEN_H
#define SO2_KITCHEN_H

#include <vector>
#include <DisplayConnector.h>
#include <Office/Rooms/KitchenItems/Cup.h>
#include <Office/Rooms/KitchenItems/Spoon.h>

struct CupSpoonPair {
    Cup *cup;
    Spoon *spoon;
};

class Kitchen : public DisplayConnector {
    using DisplayConnector::DisplayConnector;
private:
    std::vector<Cup *> cups;
    std::vector<Spoon *> spoons;
    std::mutex mutex;
public:
    void generate_cups_and_spoons(int number_of_cups);

    CupSpoonPair take_cup_and_spoon();

    void return_cup_and_spoon(CupSpoonPair cup_spoon_pair);
};


#endif //SO2_KITCHEN_H
