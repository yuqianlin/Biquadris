#include "tblock.h"

TBlock::TBlock(int level): Block{level, 'T', {std::make_pair(0, 0), std::make_pair(1, 0), std::make_pair(2, 0), std::make_pair(1, 1)}, {0, 1, 2, 4}} {}
