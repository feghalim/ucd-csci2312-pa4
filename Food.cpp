//
// Created by Mario on 4/11/2016.
//

#include "Food.h"

namespace Gaming {
    Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {

    }
    Food::~Food() {

    }
    void Food::print(std::ostream &os) const {
        os << FOOD_ID << Food::__id;
    }
}