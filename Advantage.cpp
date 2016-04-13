//
// Created by Mario on 4/11/2016.
//

#include "Advantage.h"

namespace Gaming {
    Advantage::ADVANTAGE_ID = 'D';
    Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {

    }

    void Advantage::print(std::ostream &os) const {
        os << ADVANTAGE_ID << Advantage::__id;
    }

    double Advantage::consume() {
        return __capacity * ADVANTAGE_MULT_FACTOR;
    }

    double Advantage::getCapacity() const {
        return __capacity;
    }
}