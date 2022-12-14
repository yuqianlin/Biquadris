#include "iblock.h"

IBlock::IBlock(int level): Block{level, 'I', {std::make_pair(0, 0), std::make_pair(1, 0), std::make_pair(2, 0), std::make_pair(3, 0)}} {}

std::vector<std::pair<int, int>> IBlock::rotateCW() {
    return rotateCCW(); // acts the same
}

std::vector<std::pair<int, int>> IBlock::rotateCCW() { // TODO: overlap existing IBlocks
    std::vector<std::pair<int, int>>tmp(coords);
    int index = 0;
    if (orientation == 0 || orientation == 2) {
        for (auto c = tmp.begin(); c != tmp.end(); ++c) {
            tmp[index].first -= index;
            tmp[index].second -= index;
            ++index;
        }
    } else { // vertical
        for (auto c = tmp.begin(); c != tmp.end(); ++c) {
            tmp[index].first += index;
            tmp[index].second += index;
            ++index;
        }
    }
    return tmp;
}
