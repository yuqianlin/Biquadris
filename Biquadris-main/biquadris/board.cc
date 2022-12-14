#include "board.h"
#include "block.h"
#include "level.h"
#include <iostream>
#include <utility>

using namespace std;

Board::Board(int level, int highScore, ifstream &input, Block *nextBlockObject): score{0}, highScore{highScore}, input{input}, nextBlockObject{nextBlockObject}
{
    this->level = updateLevel(level);
    this->level->attachBoard(this);
    setUp();
} 

Board::~Board() { 
    blocks.clear();
}

void Board::setUp() {
    char c = readNextBlock(input);
    char next = readNextBlock(input);
    updateBlock(c);
    setNextBlock(next);
}

char Board::getBlock(int row, int col, bool override) const {
    if (override) { // for nextBlock only
        char c = nextBlockObject->blockAt(row, col);
        if (c != ' ') {
            return c;
        } else {
            return ' ';
        }
    }
    if (blind) { // if blind is true
        if (3 <= col && col <= 9 && 3 <= row && row <= 12) { // if coordinate is within the blinded portion
            return '?'; // function returns and doesn't run the rest of the code
        }
    } // if blind is false or coordinate is not within blinded region
    for (auto b = blocks.begin(); b != blocks.end(); ++b) {
        char c = (*b)->blockAt(row, col);
        if (c != ' ') {
            return c;
        }
    }
    return ' '; // no blocks have character
}

bool Board::updateBlock(char c) {
    unique_ptr<Block>nextBlock;
    if (force) { // if force is true, nextBlock is what forceBlock is
        nextBlock = newBlock(forceBlock, level->getLevel());
        force = false; // unset force since it can only be used once
    } else {
        nextBlock = newBlock(c, level->getLevel());
    }
    if (!noOverlap(nextBlock->coords, true)) { // check for overlap before adding to board
        return false;
    } else {
        blocks.push_back(move(nextBlock));
        currentBlock = blocks.back().get();
        return true;
    }
}

char Board::readNextBlock(std::ifstream &input) {
    return level->getNextBlock(input);
}

void Board::setNextBlock(char c) {
    nextBlock = c;
    unique_ptr<Block> newNextBlock = newBlock(c, getBoardLevel());
    swap(newNextBlock, nextBlockObject);
}

char Board::getNextBlock() {
    return nextBlock;
}

void Board::replaceCurrentBlock(char c) {
    unique_ptr<Block>nextBlock = newBlock(c, getBoardLevel());
    swap(blocks.back(), nextBlock);
    currentBlock = blocks.back().get();
}

// check if new currentBlock placement (tmp) overlaps with other blocks
bool Board::noOverlap(vector<pair<int, int>> tmp, bool override, bool currBlockOverride, Block *tempCurrentBlock) {
    for (auto c : tmp) {
        // already has a different block in the cell that isn't the old currentBlock
        if (getBlock(c.first, c.second) != ' ' && getBlock(c.first, c.second) != '?') {
            if (override) {
                return false;
            }
            Block *oldBlock = currentBlock;
            if (currBlockOverride) {
                oldBlock = tempCurrentBlock;
            }
            int count = 0;
            for (auto b = oldBlock->coords.begin(); b != oldBlock->coords.end(); ++b) {
                if (*b == std::make_pair(c.first, c.second)) {
                    ++count;
                }
            }
            if (count == 0) {
                return false;
            }
        }
        // outside of board boundaries
        if (c.first < 0 || c.first > 10 || c.second >= 15) {
            return false;
        }
    }
    return true;
}

void Board::moveLeft() {
    std::vector<std::pair<int, int>> tmp = currentBlock->moveLeft();
    if (noOverlap(tmp)) { // no overlap
        tmp.swap(currentBlock->coords);
    }
    if (heavy) {
        for (int i = 0; i < 2; i++) {
            std::vector<std::pair<int, int>> tmp = currentBlock->moveDown();
            if (noOverlap(tmp)) { // no overlap
                tmp.swap(currentBlock->coords);
            }
        }
        return;
    }
    if (level->getLevel() >= 3) {
        std::vector<std::pair<int, int>> tmp = currentBlock->moveDown();
        if (noOverlap(tmp)) { // no overlap
            tmp.swap(currentBlock->coords);
        }
    }
}

void Board::moveRight() {
    std::vector<std::pair<int, int>> tmp = currentBlock->moveRight();
    if (noOverlap(tmp)) { // no overlap
        tmp.swap(currentBlock->coords);
    }
    if (heavy) {
        for (int i = 0; i < 2; i++) {
            std::vector<std::pair<int, int>> tmp = currentBlock->moveDown();
            if (noOverlap(tmp)) { // no overlap
                tmp.swap(currentBlock->coords);
            }
        }
        return;
    }
    if (level->getLevel() >= 3) {
        std::vector<std::pair<int, int>> tmp = currentBlock->moveDown();
        if (noOverlap(tmp)) { // no overlap
            tmp.swap(currentBlock->coords);
        }
    }
}

void Board::moveDown() {
    std::vector<std::pair<int, int>> tmp = currentBlock->moveDown();
    if (noOverlap(tmp)) { // no overlap
        tmp.swap(currentBlock->coords);
    }
}

void Board::rotateCW() {
    std::vector<std::pair<int, int>> tmp = currentBlock->rotateCW();
    if (noOverlap(tmp)) { // no overlap
        tmp.swap(currentBlock->coords);
        --currentBlock->orientation;
        if (currentBlock->orientation == -1) {
            currentBlock->orientation = 3;
        }
    }
    if (level->getLevel() >= 3) {
        std::vector<std::pair<int, int>> tmp = currentBlock->moveDown();
        if (noOverlap(tmp)) { // no overlap
            tmp.swap(currentBlock->coords);
        }
    }
}

void Board::rotateCCW() {
    std::vector<std::pair<int, int>> tmp = currentBlock->rotateCCW();
    if (noOverlap(tmp)) { // no overlap
        tmp.swap(currentBlock->coords);
        ++currentBlock->orientation;
        if (currentBlock->orientation == 4) {
            currentBlock->orientation = 0;
        }
    }
    if (level->getLevel() >= 3) {
        std::vector<std::pair<int, int>> tmp = currentBlock->moveDown();
        if (noOverlap(tmp)) { // no overlap
            tmp.swap(currentBlock->coords);
        }
    }
}

void Board::drop() {
    while (true) {
        std::vector<std::pair<int, int>> tmp = currentBlock->moveDown();
        if (noOverlap(tmp)) { // no overlap
            tmp.swap(currentBlock->coords);
        } else {
            unsetBlind(); // unset blind & heavy since the block has been dropped
            if (specialAction) {
                unsetHeavy();
                specialAction = false; // need to turn off special action for next use
            }
            return;
        }
    }
}

bool Board::droppedBlock() { // attempt to move a copy further down
    std::vector<std::pair<int, int>> tmp(currentBlock->coords);
    for (auto c = tmp.begin(); c != tmp.end(); ++c) {
        ++c->second;
    }
    if (!noOverlap(tmp)) { // will overlap, can't move down any more
        unsetBlind(); // unset blind & heavy since the block has been dropped
        if (specialAction) {
            unsetHeavy();
            specialAction = false;
        }
        return true;
    } else {
        return false;
    }
}

bool Board::checkClearedLine() {
    int clearCount = 0;
    for (int j = 14; j >= 0; --j) { // check each row
        bool cleared = true;
        while (cleared) {
            for (int i = 0; i < 11; ++i) {
                if (getBlock(i, j) == ' ') {
                    cleared = false;
                }
            }
            if (cleared) {
                ++clearCount;
                for (auto b = blocks.begin(); b != blocks.end(); ++b) {
                    bool removed = true;
                    for (auto c = (*b)->coords.begin(); c != (*b)->coords.end(); ++c) {
                        if (c->second == j) {
                            (*b)->coords.erase(c); // remove cell at cleared line
                            --c; // check previous coord
                        } else {
                            removed = false;
                        }
                    }
                    if (removed) {
                        score += ((*b)->levelWhenCreated + 1)*((*b)->levelWhenCreated + 1);
                        blocks.erase(b);
                        --b;
                    }
                }
            }
        }
    }
    // try to shift every block down
    for (auto b = blocks.begin(); b != blocks.end(); ++b) { // move all but current block
        bool canShift = true;
        while (canShift) {
            std::vector<std::pair<int, int>> tmp = (*b)->moveDown();
            if (noOverlap(tmp, false, true, b->get())) { // no overlap with block shifting down
                tmp.swap((*b)->coords);
            } else {
                canShift = false;
            }
        }
    }
    // update score
    if (clearCount > 0) {
        score += (level->getLevel() + clearCount)*(level->getLevel() + clearCount);
    }
    if (score > highScore) {
        highScore = score;
    }
    return (clearCount >= 2);
}

void Board::setSpecialAction(string action, char type) {
    specialAction = true;
    if (action == "blind") {
        setBlind();
    } else if (action == "heavy") {
        setHeavy();
    } else if (action == "force") {
        setForce(type);
    }
}

void Board::setBlind() {
    blind = true;
}

void Board::unsetBlind() {
    blind = false;
}

void Board::setHeavy() {
    heavy = true;
}

void Board::unsetHeavy() {
    heavy = false;
}

void Board::setForce(char type) {
    force = true;
    forceBlock = type;
}

void Board::levelUp() {
    int oldLevel = level->getLevel();
    int newLevel = ++oldLevel;
    if (newLevel == 5) { // should be 5
        return;
    }
    unique_ptr<Level>newLevelObject = updateLevel(newLevel);
    newLevelObject->attachBoard(this);
    swap(level, newLevelObject);
}

void Board::levelDown() {
    int oldLevel = level->getLevel();
    int newLevel = --oldLevel;
    if (newLevel == -1) {
        return;
    }
    unique_ptr<Level>newLevelObject = updateLevel(newLevel);
    newLevelObject->attachBoard(this);
    swap(level, newLevelObject);
}

int Board::getCount() {
    return count;
}

int Board::getBoardLevel() {
    return level->getLevel();
}

int Board::getScore() {
    return score;
}

ifstream &Board::getInput() {
    return input;
}

int Board::getHighScore() {
    return highScore;
}

int Board::getElementIndex() {
    return elementIndex;
}

void Board::resetBoard() {
    blocks.clear();
    score = 0;
    while (getBoardLevel() != 0) {
        levelDown();
    }
    setUp();
}

void Board::changeRandom(bool randomValue) {
    random = randomValue;
    level->changeRandom(randomValue);
}

void Board::increaseCount() {
    count++;
}

void Board::increaseElementIndex(int index) {
    if (index == 0) {
        elementIndex = 0;
    } else {
        ++elementIndex;
    }
}

void Board::setFileName(string newName) {
    level->setFile(newName);
    fileName = newName;
}
