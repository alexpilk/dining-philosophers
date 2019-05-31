//
// Created by Drasik on 5/30/2019.
//

#include "Kitchen.h"



void Kitchen::generate_cups_and_spoons(int number_of_cups) {
    for(int i = 0; i < number_of_cups; i++) {
        this->cups.push_back(new Cup());
        this->spoons.push_back(new Spoon());
    }
}

CupSpoonPair Kitchen::take_cup_and_spoon() {
    this->mutex.lock();
    if (this->spoons.empty() || this->cups.empty()) {
        CupSpoonPair cup_spoon_pair = {nullptr, nullptr};
        this->mutex.unlock();
        return cup_spoon_pair;
    }
    CupSpoonPair cup_spoon_pair = {this->cups[0], this->spoons[0]};
    this->cups.erase(this->cups.begin());
    this->spoons.erase(this->spoons.begin());
    this->mutex.unlock();
    return cup_spoon_pair;
}

void Kitchen::return_cup_and_spoon(CupSpoonPair cup_spoon_pair) {
    this->mutex.lock();
    this->cups.push_back(cup_spoon_pair.cup);
    this->spoons.push_back(cup_spoon_pair.spoon);
    this->mutex.unlock();
}
