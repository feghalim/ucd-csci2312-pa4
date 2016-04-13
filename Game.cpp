//
// Created by Mario on 4/11/2016.
//

#include "Game.h"
#include "Simple.h"
#include "Advantage.h"
#include "Food.h"
#include "Strategic.h"

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
        if(!manual) {
            populate();
        }
        __status = NOT_STARTED;
    }
    Game::Game(const Game &another) {
        __width = another.__width;
        __height = another.__height;
        __status = another.__status;
        __grid = another.__grid;
    }

    unsigned int Game::getNumPieces() const {
        unsigned int pieces = 0;

        for (auto it = __grid.begin(); it != __grid.end(); it++) {
            if(it != nullptr) {
                pieces++;
            }
        }

        return pieces;
    }
    unsigned int Game::getNumAgents() const {
        unsigned int agents = 0;

        for(auto it = __grid.begin(); it != __grid.end(); it++) {
            if(dynamic_cast<Agent *>(*it)) {
                agents++;
            }
        }

        return agents;
    }
    unsigned int Game::getNumSimple() const {
        unsigned int simple = 0;

        for(auto it = __grid.begin(); it != __grid.end(); it++) {
            if(dynamic_cast<Simple *>(*it)) {
                simple++;
            }
        }

        return simple;
    }
    unsigned int Game::getNumResources() const {
        unsigned int res = 0;

        for(auto it = __grid.begin(); it != __grid.end(); it++) {
            if(dynamic_cast<Resource *>(*it)) {
                res++;
            }
        }

        return res;
    }
    unsigned int Game::getNumStrategic() const {
        unsigned int strategy = 0;

        for(auto it = __grid.begin(); it != __grid.end(); it++) {
            if(dynamic_cast<Strategy *>(*it)) {
                strategy++;
            }
        }

        return strategy;
    }
    const Piece* Game::getPiece(unsigned int x, unsigned int y) const {
        unsigned int temp = y * __width;

        return __grid[temp + x];
    }

    void Game::addSimple(const Position &position) {
        unsigned int temp = position.y * __width;

        __grid[temp + position.x] = new Simple(*this, position, STARTING_AGENT_ENERGY);
    }
    void Game::addSimple(unsigned x, unsigned y) {
        Position position(x,y);
        addSimple(position);
    }
    void Game::addAdvantage(const Position &position) {
        unsigned int temp = position.y * __width;

        __grid[temp + position.x] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }
    void Game::addAdvantage(unsigned x, unsigned y) {
        Position position(x, y);
        addAdvantage(position);
    }
    void Game::addFood(const Position &position) {
        unsigned int temp = position.y * __width;

        __grid[temp + position.x] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
    }
    void Game::addFood(unsigned x, unsigned y) {
        Position position(x, y);
        addFood(position);
    }
    void Game::addStrategic(const Position &position, Strategy *s) {
        unsigned int temp = position.y * __width;

        __grid[temp + position.x] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }
    void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        Position position(x, y);
        addStrategic(position, s);
    }
    void Game::populate() {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
    }
}