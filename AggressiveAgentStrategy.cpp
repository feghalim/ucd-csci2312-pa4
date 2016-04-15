//
// Created by Mario on 4/11/2016.
//

#include "AggressiveAgentStrategy.h"
#include "Game.h"
#include "Piece.h"

namespace Gaming {

    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
        __agentEnergy = agentEnergy;
    }
    AggressiveAgentStrategy::~AggressiveAgentStrategy() {

    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
        int temp = 1000;
        bool moveKnown = false;
        bool moveAttack = false;
        ActionType ac = STAY;

        if(__agentEnergy >= DEFAULT_AGGRESSION_THRESHOLD) {
            for (int i = 0; i < 9; i++) {
                if (s.array[i] == SIMPLE || s.array[i] == STRATEGIC) {
                    temp = i;
                    i = 10;
                    moveKnown = true;
                    moveAttack = true;
                    break;
                }
            }
        }
        if(!moveKnown) {
            for(int i = 0; i < 9; i++) {
                if(s.array[i] == ADVANTAGE) {
                    temp = i;
                    i = 10;
                    moveKnown = true;
                    moveAttack = false;
                    break;
                }
            }
            if(!moveKnown) {
                for(int i = 0; i < 9; i++) {
                    if(s.array[i] == FOOD) {
                        temp = i;
                        i = 10;
                        moveKnown = true;
                        moveAttack = false;
                        break;
                    }
                }
                if(!moveKnown) {
                    for(int i = 0; i < 9; i++) {
                        if(s.array[i] == EMPTY) {
                            temp = i;
                            i = 10;
                            moveKnown = true;
                            moveAttack = false;
                            break;
                        }
                    }
                }
            }
        }

        if(moveKnown && moveAttack) {
            switch(temp) {
                case 0:
                    ac = NW;
                    break;
                case 1:
                    ac = N;
                    break;
                case 2:
                    ac = NE;
                    break;
                case 3:
                    ac = W;
                    break;
                case 4:
                    ac = STAY;
                    break;
                case 5:
                    ac = E;
                    break;
                case 6:
                    ac = SW;
                    break;
                case 7:
                    ac = S;
                    break;
                case 8:
                    ac = SE;
                    break;
                default:
                    ac = STAY;
                    break;
            }
        }
        else if(moveKnown && !moveAttack) {
            switch(temp) {
                case 0:
                    ac = NW;
                    break;
                case 1:
                    ac = N;
                    break;
                case 2:
                    ac = NE;
                    break;
                case 3:
                    ac = W;
                    break;
                case 4:
                    ac = STAY;
                    break;
                case 5:
                    ac = E;
                    break;
                case 6:
                    ac = SW;
                    break;
                case 7:
                    ac = S;
                    break;
                case 8:
                    ac = SE;
                    break;
                default:
                    ac = STAY;
                    break;
            }
        }
        else {
            ac = STAY;
        }
        return ac;
    }
}