#include "block.h"
#include "iblock.h"
#include "oblock.h"
#include "jblock.h"
#include "lblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "starblock.h"
#include <iostream>
#include <memory>
using namespace std;
class Board;

Block::Block(int levelWhenCreated, char blockChar, std::vector<std::pair<int, int>> coords, std::vector<int> positions): levelWhenCreated{levelWhenCreated}, blockChar{blockChar}, coords{coords}, positions{positions} {}

unique_ptr<Block>newBlock(char c, int level) { // factory method pattern
    if (c == 'I') {
        return make_unique<IBlock>(level);
    } else if (c == 'O') {
        return make_unique<OBlock>(level);
    } else if (c == 'Z') {
        return make_unique<ZBlock>(level);
    } else if (c == 'S') {
        return make_unique<SBlock>(level);
    } else if (c == 'T') {
        return make_unique<TBlock>(level);
    } else if (c == 'L') {
        return make_unique<LBlock>(level);
    } else if (c == 'J') {
        return make_unique<JBlock>(level);
    } else { //if c == *
        return make_unique<StarBlock>(level);
    }
}

char Block::blockAt(int x, int y) {
    for (auto c : coords) {
        if (x == c.first && y == c.second) {
            return blockChar;
        }
    }
    return ' ';
}

std::vector<std::pair<int, int>> Block::moveLeft() {
    std::vector<std::pair<int, int>> tmp(coords); 
    for (auto c = tmp.begin(); c != tmp.end(); ++c) {
        --c->first;
    }
    return tmp;
}

std::vector<std::pair<int, int>> Block::moveRight() {
    std::vector<std::pair<int, int>> tmp(coords);
    for (auto c = tmp.begin(); c != tmp.end(); ++c) {
        ++c->first;
    }
    return tmp;
}

std::vector<std::pair<int, int>> Block::moveDown() {
    std::vector<std::pair<int, int>> tmp(coords);
    for (auto c = tmp.begin(); c != tmp.end(); ++c) {
        ++c->second;
    }
    return tmp;
}

std::vector<std::pair<int, int>> Block::rotateCW() {
    std::vector<std::pair<int, int>> tmp(coords);
    for (int i = 0; i < 4; ++i) {
        rotateCellCW(tmp[i], positions[i], orientation);
    }
    return tmp;
}

std::vector<std::pair<int, int>> Block::rotateCCW() {
    std::vector<std::pair<int, int>> tmp(coords);
    for (int i = 0; i < 4; ++i) {
        rotateCellCCW(tmp[i], positions[i], orientation);
    }
    return tmp;
}

#include <iostream>

void Block::rotateCellCW(std::pair<int, int> &coords, int position, int orientation) {
    int &x = coords.first;
    int &y = coords.second;
    if (orientation == 0) {
        if (position == 0) {
            ++x;
            --y;
        } else if (position == 1) {
            return;
        } else if (position == 2) {
            --x;
            ++y;
        } else if (position == 3) {
            y -= 2;
        } else if (position == 4) {
            --x;
            --y;
        } else { // position = 5
            x -= 2;
        }
    } else if (orientation == 1) {
        if (position == 0) {
            --y;
        } else if (position == 1) {
            ++x;
        } else if (position == 2) {
            x += 2;
            ++y;
        } else if (position == 3) {
            --x;
        } else if (position == 4) {
            ++y;
        } else if (position == 5) {
            ++x;
            y += 2;
        }
    } else if (orientation == 2) {
        if (position == 0) {
            x -= 2;
        } else if (position == 1) {
            --x;
            --y;
        } else if (position == 2) {
            y -= 2;
        } else if (position == 3) {
            --x;
            ++y;
        } else if (position == 4) {
            return;
        } else { // position = 5
            ++x;
            --y;
        }
    } else { // orientation = 3
        if (position == 0) {
            ++x;
            y += 2;
        } else if (position == 1) {
            ++y;
        } else if (position == 2) {
            --x;
        } else if (position == 3) {
            x += 2;
            ++y;
        } else if (position == 4) {
            ++x;
        } else if (position == 5) {
            --y;
        }
    }
}

void Block::rotateCellCCW(std::pair<int, int> &coords, int position, int orientation) {
    int &x = coords.first;
    int &y = coords.second;
    if (orientation == 0) {
        if (position == 0) {
            ++y;
        } else if (position == 1) {
            --x;
        } else if (position == 2) {
            x -= 2;
            y -= 1;
        } else if (position == 3) {
            ++x;
        } else if (position == 4) {
            --y;
        } else { // position = 5
            --x;
            y -= 2;
        }
    } else if (orientation == 1) {
        if (position == 0) {
            x += 2;
        } else if (position == 1) {
            ++x;
            ++y;
        } else if (position == 2) {
            y += 2;
        } else if (position == 3) {
            ++x;
            --y;
        } else if (position == 4) {
            return;
        } else if (position == 5) {
            ++y;
            --x;
        }
    } else if (orientation == 2) {
        if (position == 0) {
            --x;
            y -= 2;
        } else if (position == 1) {
            --y;
        } else if (position == 2) {
            ++x;
        } else if (position == 3) {
            x -= 2;
            --y;
        } else if (position == 4) {
            --x;
        } else { // position = 5
            ++y;
        }
    } else { // orientation = 3
        if (position == 0) {
            --x;
            ++y;
        } else if (position == 1) {
            return;
        } else if (position == 2) {
            ++x;
            --y;
        } else if (position == 3) {
            y += 2;
        } else if (position == 4) {
            ++x;
            ++y;
        } else if (position == 5) {
            x += 2;
        }
    }
}

Block::~Block() {
    coords.clear();
    positions.clear();
}
