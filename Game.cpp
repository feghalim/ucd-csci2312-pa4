//
// Created by Mario on 4/11/2016.
//

#include <set>
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
    PositionRandomizer Game::__posRandomizer = PositionRandomizer();

    Game::Game() {
        __width = MIN_WIDTH;
        __height = MIN_HEIGHT;
        __round = 0;

        for(int i = 0; i < __width * __height; i ++) {
            __grid.push_back(nullptr);
        }

        __status = NOT_STARTED;
    }
    Game::Game(unsigned width, unsigned height, bool manual) {
        __width = width;
        __height = height;

        for(int i = 0; i < __width * __height; i ++) {
            __grid.push_back(nullptr);
        }

        if(!manual) {
            populate();
        }
        __status = NOT_STARTED;
    }
    Game::Game(const Game &another) {
        __width = another.__width;
        __height = another.__height;
        __status = another.__status;
        for(int i = 0; i < (__width * __height); i++) {
            __grid[i] = another.__grid[i];
        }
    }
    Game::~Game() {
        for(auto it = __grid.begin(); it != __grid.end(); it++) {
            if(*it != nullptr) {
                delete *it;
            }
        }
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
        unsigned int strategic = 0;

        for(auto it = __grid.begin(); it != __grid.end(); it++) {
            if(dynamic_cast<Strategic *>(*it)) {
                strategic++;
            }
        }

        return strategic;
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
        Surroundings piece;

        for(int i = 0; i < 9; i++) {
            piece.array[i] = EMPTY;
        }

        row: for(int i = -1; i <= 1; i++) {
            column: for(int k = -1; k <= 1; k++) {
                if(pos.x + i >= 0 && pos.x + i < __height && pos.y + k >= 0 && pos.y + k < __width) {
                    int temp = pos.y + k + (pos.x + i) * __width;
                    if(__grid[temp]) {
                        piece.array[k + 1 + ((i + 1) * 3)] = __grid[temp]->getType();
                    }
                }
                else {
                    piece.array[k + 1 + ((i + 1) * 3)] = INACCESSIBLE;
                }
            }
        }
        piece.array[4] = SELF;

        return piece;

    }
    const ActionType Game::reachSurroundings(const Position &from, const Position &to) {
        if(from.x == to.x && from.y == to.y) {
            return STAY;
        }
        if(from.x < to.x && from.y == to.y) {
            return W;
        }
        if(from.x > to.x && from.y == to.y) {
            return E;
        }
        if(from.x == to.x && from.y < to.y) {
            return S;
        }
        if(from.x == to.x && from.y > to.y) {
            return N;
        }
        if(from.x < to.x && from.y < to.y) {
            return SW;
        }
        if(from.x < to.x && from.y > to.y) {
            return NW;
        }
        if(from.x > to.x && from.y < to.y) {
            return SE;
        }
        if(from.x > to.x && from.y > to.y) {
            return NE;
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
                return Position(pos.x, pos.y - 1);
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
        std::set<Piece *> pieces;
        for(auto it = __grid.begin(); it != __grid.end(); it++) {
            if(*it) {
                pieces.insert(pieces.end(), *it);
                (*it)->setTurned(true);
            }
        }

        for(auto it = pieces.begin(); it != pieces.end(); it++) {
            if(!(*it)->getTurned()) {
                (*it)->setTurned(true);
                (*it)->age();
                ActionType ac = (*it)->takeTurn(getSurroundings((*it)->getPosition()));
                Position pos = (*it)->getPosition();
                Position pos2 = move(pos, ac);
                if(pos.x != pos2.x || pos.y != pos2.y) {
                    Piece *p = __grid[pos2.y * __width + pos2.x];
                    if(p) {
                        (*(*it) * (*p));
                        if ((*it)->getPosition().x != pos.x || (*it)->getPosition().y != pos.y) {
                            __grid[pos2.y + (pos2.x * __width)] = (*it);
                            __grid[pos.y + (pos.x * __width)] = p;
                        }
                        else {
                            // empty move
                            (*it)->setPosition(pos2);
                            __grid[pos2.y * __width + pos2. x] = (*it);
                            __grid[pos.y * __width + pos.x] = nullptr;
                        }
                    }
                }
            }
        }

        for (unsigned int i = 0; i < __grid.size(); ++i) {
            if (__grid[i] && !(__grid[i]->isViable())) {
                delete __grid[i];
                __grid[i] = nullptr;
            }
        }

        if (getNumResources() <= 0) {
            __status = OVER;
        }
        __round++;
    }
    void Game::play(bool verbose) {
        __verbose = verbose;
        __status = PLAYING;
        std::cout << *this;
        while(__status != OVER) {
            round();
            if(verbose) {
                std::cout << *this;
            }
        }
        if(!verbose) {
            std::cout << *this;
        }
    }
    void Game::populate() {
        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategicRemaining = __numInitAgents / 2;
        unsigned int numSimpleRemaining = __numInitAgents - numStrategicRemaining;
        unsigned int numAdvantagesRemaining = __numInitResources / 4;
        unsigned int numFoodRemaining = __numInitResources - numAdvantagesRemaining;

        std::default_random_engine randPieceGenerator;
        std::uniform_int_distribution<int> pieceRange(0, __width * __height);

        while(numStrategicRemaining > 0) {
            int i = pieceRange(randPieceGenerator);
            if(__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
                numStrategicRemaining--;
            }
        }
        while(numSimpleRemaining > 0) {
            int i = pieceRange(randPieceGenerator);
            if(__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, Game::STARTING_AGENT_ENERGY);
                numSimpleRemaining--;
            }
        }
        while(numAdvantagesRemaining > 0) {
            int i = pieceRange(randPieceGenerator);
            if(__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, Game::STARTING_RESOURCE_CAPACITY);
                numAdvantagesRemaining--;
            }
        }
        while(numFoodRemaining > 0) {
            int i = pieceRange(randPieceGenerator);
            if(__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, Game::STARTING_AGENT_ENERGY);
                numFoodRemaining--;
            }
        }
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