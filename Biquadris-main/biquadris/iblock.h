#ifndef IBLOCK_H
#define IBLOCK_H

#include "block.h"

class IBlock: public Block {
    virtual std::vector<std::pair<int, int>> rotateCCW() override;
    virtual std::vector<std::pair<int, int>> rotateCW() override;
public:
    IBlock(int level);
};

#endif
