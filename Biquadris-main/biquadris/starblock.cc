#include "starblock.h"

StarBlock::StarBlock(int level): Block{level, '*', {std::make_pair(5, 0)}} {}

std::vector<std::pair<int, int>> StarBlock::rotateCW() {
    return coords; // do nothing
}

std::vector<std::pair<int, int>> StarBlock::rotateCCW() {
    return coords; // do nothing
}
