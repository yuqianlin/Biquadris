#ifndef OBLOCK_H
#define OBLOCK_H

#include "block.h"

class OBlock: public Block {
    virtual std::vector<std::pair<int, int>> rotateCCW() override;
    virtual std::vector<std::pair<int, int>> rotateCW() override;
public:
    OBlock(int level);
};

#endif
