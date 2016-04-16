//
// Created by Mario on 4/11/2016.
//

#include "Advantage.h"
#include "sstream"

namespace Gaming {
    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity * ADVANTAGE_MULT_FACTOR) {
        __capacity = capacity * ADVANTAGE_MULT_FACTOR;
    }
    Advantage::~Advantage() {

    }

    void Advantage::print(std::ostream &os) const {
        std::string str;
        str = std::to_string(__id);

        std::stringstream ss;
        ss << ADVANTAGE_ID << str;
        std::getline(ss, str);

        for(int i = 0; i < str.length(); i++) {
            os << str[i];
        }
    }

    double Advantage::consume() {
        double capacity = __capacity;
        __capacity = -1;
        finish();
        return capacity;
    }

    double Advantage::getCapacity() const {
        return __capacity;
    }
}