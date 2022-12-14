#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <utility>
#include <memory>
class Board;

class Block {
    friend class Board; // board can access blocks
    std::vector<std::pair<int, int>> moveLeft();
    std::vector<std::pair<int, int>> moveRight();
    std::vector<std::pair<int, int>> moveDown();
    virtual std::vector<std::pair<int, int>> rotateCW();
    virtual std::vector<std::pair<int, int>> rotateCCW();
    char blockAt(int x, int y);
protected: // TODO: figure this out
    int levelWhenCreated;
    char blockChar;
    std::vector<std::pair<int, int>> coords;
    std::vector<int> positions; // useless for lblock, oblock
    int orientation = 0;
    void rotateCellCW(std::pair<int, int> &coords, int position, int orientation);
    void rotateCellCCW(std::pair<int, int> &coords, int position, int orientation);
public:
    Block(int levelWhenCreated, char blockChar, std::vector<std::pair<int, int>> coords, std::vector<int> positions = {0}); // no p for lblock, oblock
    virtual ~Block() = 0;
};

std::unique_ptr<Block>newBlock(char c, int level);

#endif
