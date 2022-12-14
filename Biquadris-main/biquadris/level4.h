#ifndef LEVEL_FOUR_H
#define LEVEL_FOUR_H

#include "level.h"
#include "block.h"

class LevelFour: public Level{
    private:
    friend class Board;
    char getNextBlock(std::ifstream &fileStream) override;

    public:
    LevelFour();
    
};

#endif
