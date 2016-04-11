//
// Created by Mario on 4/11/2016.
//

#include "Game.h"
#include "Simple.h"

namespace Gaming {
    Game::Game() {
        __width = 3;
        __height = 3;
        __round = 0;
        populate();
        __status = NOT_STARTED;
    }
    Game::Game(unsigned width, unsigned height, bool manual) {
        __width = width;
        __height = height;
        __status = NOT_STARTED;
    }
    Game::Game(const Game &another) {
        __width = another.__width;
        __height = another.__height;
        __status = another.__status;
        __grid = another.__grid;
    }
    Game& Game::operator=(const Game &other) {
        return Game(other);
    }

    unsigned int Game::getNumPieces() const {
        return __grid.size;
    }
    unsigned int Game::getNumAgents() const {

    }
    unsigned int Game::getNumSimple() const {

    }
    unsigned int Game::getNumResources() const {

    }
    unsigned int Game::getNumStrategic() const {

    }
    const Piece* Game::getPiece(unsigned int x, unsigned int y) const {
        unsigned int temp = y * __width;

        return __grid[temp + x];
    }

    void Game::addSimple(const Position &position) {
        Simple simple(*this, position, 100);
        __grid[position] = simple;
    }
    void Game::addSimple(unsigned x, unsigned y) {
        Position position = y * __width + x;
        addSimple(position);
    }
}