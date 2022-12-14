#include "oblock.h"

OBlock::OBlock(int level): Block{level, 'O', {std::make_pair(0, 0), std::make_pair(1, 0), std::make_pair(0, 1), std::make_pair(1, 1)}} {}

std::vector<std::pair<int, int>> OBlock::rotateCW() {
    return coords; // do nothing
}

std::vector<std::pair<int, int>> OBlock::rotateCCW() {
    return coords; // do nothing
}
