#ifndef LEVEL_TWO_H
#define LEVEL_TWO_H

#include "level.h"
#include "block.h"
class LevelTwo: public Level{
    private:
    char getNextBlock(std::ifstream &fileStream) override;

    public:
    LevelTwo();
    
};

#endif
