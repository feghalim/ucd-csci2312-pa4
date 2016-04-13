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
            other->addEnergy(__energy * -1);
            this->finish();
            return *this;
        }
        else if(other->getEnergy() < this->getEnergy()) {
            __energy += other->getEnergy();
            other->finish();
            return *this;
        }
    }
    Piece& Agent::interact(Resource *other) {
        addEnergy(other->consume());
        return *this;
    }
    Piece& Agent::operator*(Piece &other) {
        other.interact(this);
        return *this;
    }

}