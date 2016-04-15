//
// Created by Mario on 4/11/2016.
//

#include "Food.h"
#include "sstream"

namespace Gaming {
    const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {
        __capacity = capacity;
    }
    Food::~Food() {

    }
    void Food::print(std::ostream &os) const {
        std::string str;
        str = std::to_string(__id);

        std::stringstream ss;
        ss << FOOD_ID << str;
        std::getline(ss, str);

        for(int i = 0; i < str.length(); i++) {
            os << str[i];
        }
    }
}