#ifndef STARBLOCK_H
#define STARBLOCK_H

#include "block.h"

class StarBlock: public Block {
    virtual std::vector<std::pair<int, int>> rotateCCW() override;
    virtual std::vector<std::pair<int, int>> rotateCW() override;
public:
    StarBlock(int level);
};

#endif
