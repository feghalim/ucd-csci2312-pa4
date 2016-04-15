//
// Created by Mario on 4/11/2016.
//

#include "Resource.h"

namespace Gaming {
    const double Resource::RESOURCE_SPOIL_FACTOR = 2.0;

    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g, p) {
        __capacity = capacity;
    }
    Resource::~Resource() {

    }

    void Resource::age() {
        __capacity /= RESOURCE_SPOIL_FACTOR;
        if(__capacity < 1) {
            finish();
        }
    }
    double Resource::consume() {
        double consume = __capacity;
        __capacity = 0;
        finish();
        return consume;
    }
    ActionType Resource::takeTurn(const Surroundings &s) const {
        return STAY;
    }

    Piece& Resource::operator*(Piece &other) {

    }
    Piece& Resource::interact(Agent *other) {
        return *this;
    }
    Piece& Resource::interact(Resource *other) {
        return *this;
    }
}