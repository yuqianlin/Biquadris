#include "sblock.h"

SBlock::SBlock(int level): Block{level, 'S', {std::make_pair(2, 0), std::make_pair(1, 0), std::make_pair(1, 1), std::make_pair(0, 1)}, {2, 1, 4, 3}} {}
