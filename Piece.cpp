//
// Created by Mario on 4/11/2016.
//

#include "Piece.h"

namespace Gaming {
    unsigned int Piece::__idGen = 0;

    Piece::Piece(const Game &g, const Position &p) : __game(g) {
        __position = p;
        __id = __idGen++;
    }
    Piece::~Piece() {

    }
    Piece& Piece::operator*(Piece &other) {
        return other;
    }

}