#include "zblock.h"

ZBlock::ZBlock(int level): Block{level, 'Z', {std::make_pair(0, 0), std::make_pair(1, 0), std::make_pair(1, 1), std::make_pair(2, 1)}, {0, 1, 4, 5}} {}
