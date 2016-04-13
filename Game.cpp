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
        populate();
        __status = NOT_STARTED;
    }
    Game::Game(const Game &another) {
        __width = another.__width;
        __height = another.__height;
        __status = another.__status;
        __grid = another.__grid;
    }

    unsigned int Game::getNumPieces() const {
        unsigned int pieces = __grid.size();
        return pieces;
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

    }
    void Game::addSimple(unsigned x, unsigned y) {
        Position position(x,y);
        addSimple(position);
    }
    void Game::populate() {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
    }
}