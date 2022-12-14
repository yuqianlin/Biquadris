#include "lblock.h"

LBlock::LBlock(int level): Block{level, 'L', {std::make_pair(2, 0), std::make_pair(2, 1), std::make_pair(1, 1), std::make_pair(0, 1)}, {2, 5, 4, 3}} {}
