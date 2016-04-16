//
// Created by Mario on 4/11/2016.
//

#include "Agent.h"
#include "Resource.h"

namespace Gaming {
    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p) {
        __energy = energy;
    }
    Agent::~Agent() {

    }
    void Agent::age() {
        __energy -= AGENT_FATIGUE_RATE;
    }
    Piece& Agent::interact(Agent *other) {
        if(other->getEnergy() == this->getEnergy()) {
            other->finish();
            this->finish();
        }
        else if(other->getEnergy() > this->getEnergy()) {
            other->__energy -= this->getEnergy();
            this->finish();
        }
        else if(other->getEnergy() < this->getEnergy()) {
            __energy -= other->getEnergy();
            other->finish();
        }
        return *this;
    }
    Piece& Agent::interact(Resource *other) {
        __energy += other->consume();
        return *this;
    }
    Piece& Agent::operator*(Piece &other) {
        Piece *piece = &other;
        Resource *resource = dynamic_cast<Resource *>(piece);
        if(resource) {
            interact(resource);
        }
        Agent *agent = dynamic_cast<Agent *>(piece);
        if(agent) {
            interact(agent);
        }
        if(!isFinished()) {
            Position newPos;
            newPos = other.getPosition();
            Position oldPos;
            oldPos = getPosition();
            setPosition(newPos);
            other.setPosition(oldPos);
        }
        return *this;
    }

}