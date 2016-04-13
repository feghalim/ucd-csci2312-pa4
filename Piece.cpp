//
// Created by Mario on 4/11/2016.
//

#include "Piece.h"

namespace Gaming {
    Piece::Piece(const Game &g, const Position &p) : __game(g) {
        __position = p;
    }
    Piece::~Piece() {

    }
    Piece& Piece::operator*(Piece &other) {
        return other;
    }

}