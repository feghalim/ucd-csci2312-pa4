//
// Created by Mario on 4/11/2016.
//

#include "Game.h"
#include "Simple.h"
#include "Advantage.h"
#include "Food.h"
#include "Strategic.h"

namespace Gaming {
    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

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

        if(pos.x == 0 && pos.y == 0) {
            piece.array[0] = INACCESSIBLE;
            piece.array[1] = INACCESSIBLE;
            piece.array[3] = INACCESSIBLE;
            piece.array[4] = SELF;
        }
        else if(pos.x == 0 && pos.y == __height) {
            piece.array[3] = INACCESSIBLE;
            piece.array[6] = INACCESSIBLE;
            piece.array[7] = INACCESSIBLE;
            piece.array[4] = SELF;
        }
        else if (pos.x == __width && pos.y == 0) {
            piece.array[1] = INACCESSIBLE;
            piece.array[2] = INACCESSIBLE;
            piece.array[5] = INACCESSIBLE;
            piece.array[4] = SELF;
        }
        else if(pos.x == __width && pos.y == __height) {
            piece.array[5] = INACCESSIBLE;
            piece.array[7] = INACCESSIBLE;
            piece.array[8] = INACCESSIBLE;
            piece.array[4] = SELF;
        }
        else if(pos.x == 0) {
            piece.array[0] = INACCESSIBLE;
            piece.array[3] = INACCESSIBLE;
            piece.array[6] = INACCESSIBLE;
            piece.array[4] = SELF;
        }
        else if(pos.x == __width) {
            piece.array[2] = INACCESSIBLE;
            piece.array[5] = INACCESSIBLE;
            piece.array[8] = INACCESSIBLE;
            piece.array[4] = SELF;
        }
        else if(pos.y == 0) {
            piece.array[0] = INACCESSIBLE;
            piece.array[1] = INACCESSIBLE;
            piece.array[2] = INACCESSIBLE;
            piece.array[4] = SELF;
        }
        else if(pos.y == __height) {
            piece.array[6] = INACCESSIBLE;
            piece.array[7] = INACCESSIBLE;
            piece.array[9] = INACCESSIBLE;
            piece.array[4] = SELF;
        }
        else {
            piece.array[4] = SELF;
        }

        for(int i = 0; i < 9; i++) {
            if(i != 4) {
                if(i < 4) {
                    if(__grid[temp - i] != nullptr) {
                        piece.array[i] = __grid[temp - i]->getType();
                    }
                    else {
                        if(piece.array[i] != INACCESSIBLE) {
                            piece.array[i] = EMPTY;
                        }
                        else {
                            piece.array[i] = INACCESSIBLE;
                        }
                    }
                }
                if(i > 4) {
                    if(__grid[temp + i] != nullptr) {
                        piece.array[i] = __grid[temp + i]->getType();
                    }
                    else {
                        if(piece.array[i] != INACCESSIBLE) {
                            piece.array[i] = EMPTY;
                        }
                        else {
                            piece.array[i] = INACCESSIBLE;
                        }
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
    bool Game::isLegal(const ActionType &ac, const Position &pos) const {
        Surroundings piece;
        bool legal = false;

        for(int i = 0; i < 9; i++) {
            piece.array[i] = getSurroundings(pos).array[i];
        }

        switch(ac) {
            case STAY:
                legal = true;
                break;
            case N:
                if(piece.array[1] != INACCESSIBLE) {
                    legal = true;
                }
                break;
            case S:
                if(piece.array[7] != INACCESSIBLE) {
                    legal = true;
                }
                break;
            case E:
                if(piece.array[3] != INACCESSIBLE) {
                    legal = true;
                }
                break;
            case W:
                if(piece.array[5] != INACCESSIBLE) {
                    legal = true;
                }
                break;
            case NE:
                if(piece.array[0] != INACCESSIBLE) {
                    legal = true;
                }
                break;
            case NW:
                if(piece.array[2] != INACCESSIBLE) {
                    legal = true;
                }
                break;
            case SE:
                if(piece.array[6] != INACCESSIBLE) {
                    legal = true;
                }
                break;
            case SW:
                if(piece.array[8] != INACCESSIBLE) {
                    legal = true;
                }
                break;
            default:
                break;
        }
        return legal;
    }
    const Position Game::move(const Position &pos, const ActionType &ac) const {
        if(isLegal(ac, pos)) {
            if(ac == STAY) {
                return pos;
            }
            if(ac == E) {
                return Position(pos.x + 1, pos.y);
            }
            if(ac == W) {
                return Position(pos.x - 1, pos.y);
            }
            if(ac == S) {
                return Position(pos.x, pos.y + 1);
            }
            if(ac == N) {
                return Position(pos.x, pos.y + 1);
            }
            if(ac == SE) {
                return Position(pos.x + 1, pos.y + 1);
            }
            if(ac == NE) {
                return Position(pos.x + 1, pos.y - 1);
            }
            if(ac == SW) {
                return Position(pos.x - 1, pos.x + 1);
            }
            if(ac == NW) {
                return Position(pos.x - 1, pos.y - 1);
            }
        }
        else {
            return pos;
        }
    }
    void Game::round() {
        __round++;
    }
    void Game::play(bool verbose) {

    }
    void Game::populate() {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
    }

    std::ostream &operator<<(std::ostream &os, const Game &game) {
        for(unsigned int i = 0; i < game.__width * game.__height; i++) {
            if(game.__grid[i] == nullptr) {
                os << "[   ]";
            }
            else {
                os << "[" << game.__grid[i] << "]";
            }

            if(i % game.__width == 0) {
                os << std::endl;
            }

        }
        os << "Status: " << game.getStatus() << std::endl;

        return os;
    }
}