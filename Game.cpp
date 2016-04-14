//
// Created by Mario on 4/11/2016.
//

#include "Game.h"
#include "Simple.h"
#include "Advantage.h"
#include "Food.h"
#include "Strategic.h"

namespace Gaming {
    const unsigned int NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned MIN_WIDTH = 3;
    const unsigned MIN_HEIGHT = 3;
    const double STARTING_AGENT_ENERGY = 20;
    const double STARTING_RESOURCE_ENERGY = 10;

    Game::Game() {
        __width = MIN_WIDTH;
        __height = MIN_HEIGHT;
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
    Game::~Game() {

    }

    unsigned int Game::getNumPieces() const {
        unsigned int pieces = 0;

        for (auto it = __grid.begin(); it != __grid.end(); it++) {
            if(*it != nullptr) {
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
    void Game::addSimple(const Position &position, double energy) {
        unsigned int temp = position.y * __width;

        __grid[temp + position.x] = new Simple(*this, position, energy);
    }
    void Game::addSimple(unsigned x, unsigned y) {
        Position position(x,y);
        addSimple(position);
    }
    void Game::addSimple(unsigned x, unsigned y, double energy) {
        Position position(x,y);
        addSimple(position, energy);
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
    const Surroundings Game::getSurroundings(const Position &pos) const {
        unsigned int temp = pos.y * __width + pos.x;

        Surroundings piece;

        for(int i = 0; i < 9; i++) {
            if(i != 4) {
                if(i < 4) {
                    if(__grid[temp - i] != nullptr) {
                        piece.array[i] = __grid[temp - i]->getType();
                    }
                    else {
                        piece.array[i] = EMPTY;
                    }
                }
                if(i > 4) {
                    if(__grid[temp + i] != nullptr) {
                        piece.array[i] = __grid[temp + i]->getType();
                    }
                    else {
                        piece.array[i] = EMPTY;
                    }
                }
            }
            else {
                piece.array[4] = SELF;
            }
        }
        return piece;
    }
    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {
        if(from.x == to.x && from.y == to.y) {
            return STAY;
        }
        if(from.x < to.x && from.y == to.y) {
            return E;
        }
        if(from.x > to.x && from.y == to.y) {
            return W;
        }
        if(from.x == to.x && from.y < to.y) {
            return S;
        }
        if(from.x == to.x && from.y > to.y) {
            return N;
        }
        if(from.x < to.x && from.y < to.y) {
            return SE;
        }
        if(from.x < to.x && from.y > to.y) {
            return NE;
        }
        if(from.x > to.x && from.y < to.y) {
            return SW;
        }
        if(from.x > to.x && from.y > to.y) {
            return NW;
        }
    }
    void Game::populate() {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
    }
}