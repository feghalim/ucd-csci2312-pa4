//
// Created by Mario on 4/11/2016.
//

#include <sstream>
#include "Simple.h"

namespace Gaming {
    const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p , energy) {
        __energy = energy;
    }
    Simple::~Simple() {

    }

    void Simple::print(std::ostream &os) const {
        std::string str;
        str = std::to_string(__id);

        std::stringstream ss;
        ss << SIMPLE_ID << str;
        std::getline(ss, str);

        for(int i = 0; i < str.length(); i++) {
            os << str[i];
        }
    }
    ActionType Simple::takeTurn(const Surroundings &s) const {
        int temp = 1000;
        ActionType ac;
        bool moveKnown = false;

        for(int i = 0; i < 9; i++) {
            if(s.array[i] == FOOD || s.array[i] == ADVANTAGE) {
                temp = i;
                moveKnown = true;
                i = 10;
                break;
            }
        }
        if(!moveKnown) {
            for(int i = 0; i < 9; i++) {
                if(s.array[i] == EMPTY);
                temp = i;
                moveKnown = true;
                i = 10;
                break;
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