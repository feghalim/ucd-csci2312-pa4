//
// Created by Mario on 4/11/2016.
//

#include "Agent.h"

namespace Gaming {
    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p) {
        __energy = energy;
    }
    void Agent::age() {
        __energy -= AGENT_FATIGUE_RATE;
    }
    Piece& Agent::interact(Agent *other) {
        if(other->getEnergy() == this->getEnergy()) {
            other->finish();
            this->finish();
            return *this;
        }
        else if(other->getEnergy() > this->getEnergy()) {
            this->finish();
            return *this;
        }
        else if(other->getEnergy() < this->getEnergy()) {
            other->finish();
            return *this;
        }
    }
    Piece& Agent::interact(Resource *other) {
        if(other->getType() == FOOD) {
            __energy += other->getCapacity();
            other->finish();
        }
        else if(other->getType() == ADVANTAGE) {
            __energy *= other->ADVANTAGE_MULT_FACTOR;
            other->finish();
        }
        return *this;
    }

}