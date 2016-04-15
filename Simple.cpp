//
// Created by Mario on 4/11/2016.
//

#include "Simple.h"

namespace Gaming {
    const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p , energy) {

    }
    void Simple::print(std::ostream &os) const {
        os << SIMPLE_ID << __id;
    }
    ActionType Simple::takeTurn(const Surroundings &s) const {
        unsigned int temp;
        ActionType ac;

        for(int i = 0; i < 9; i++) {
            if(s.array[i] == FOOD || s.array[i] == ADVANTAGE) {
                temp = i;
                i = 10;
                break;
            }
        }
        switch(temp) {
            case 0:
                ac = NE;
                break;
            case 1:
                ac = N;
                break;
            case 2:
                ac = NW;
                break;
            case 3:
                ac = E;
                break;
            case 4:
                ac = STAY;
                break;
            case 5:
                ac = W;
                break;
            case 6:
                ac = SE;
                break;
            case 7:
                ac = S;
                break;
            case 8:
                ac = SW;
                break;
            default:
                ac = STAY;
                break;
        }
        return ac;
    }
}