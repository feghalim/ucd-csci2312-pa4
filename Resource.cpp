//
// Created by Mario on 4/11/2016.
//

#include "Resource.h"

namespace Gaming {
    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g, p) {
        __capacity = capacity;
    }
    void Resource::age() {
        __capacity /= RESOURCE_SPOIL_FACTOR;
    }
    double Resource::consume() {
        return --__capacity;
    }
    ActionType Resource::takeTurn(const Surroundings &s) const {
        return STAY;
    }
}