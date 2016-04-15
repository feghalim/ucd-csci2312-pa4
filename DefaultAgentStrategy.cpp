//
// Created by Mario on 4/11/2016.
//

#include "DefaultAgentStrategy.h"

namespace Gaming {
    DefaultAgentStrategy::DefaultAgentStrategy() {

    }
    DefaultAgentStrategy::~DefaultAgentStrategy() {

    }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {
        int temp = 1000;
        bool moveKnown = false;
        ActionType ac = STAY;

        for(int i = 0; i < 9; i++) {
            if(s.array[i] == ADVANTAGE) {
                temp = i;
                moveKnown = true;
                i = 10;
                break;
            }
        }
        if(!moveKnown) {
            for(int i = 0; i < 9; i++) {
                if(s.array[i] == FOOD) {
                    temp = i;
                    moveKnown = true;
                    i = 10;
                    break;
                }
            }
            if(!moveKnown) {
                for(int i = 0; i < 9; i++) {
                    if(s.array[i] == EMPTY) {
                        temp = i;
                        moveKnown = true;
                        i = 10;
                        break;
                    }
                }
                if(!moveKnown) {
                    for(int i = 0; i < 9; i++) {
                        if(s.array[i] == SIMPLE) {
                            temp = i;
                            moveKnown = true;
                            i = 10;
                            break;
                        }
                    }
                }
            }
        }

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
        return ac;
    }
}