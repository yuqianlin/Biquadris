#ifndef LEVEL_ONE_H
#define LEVEL_ONE_H

#include "level.h"
#include "block.h"
class LevelOne: public Level{
    private:
    char getNextBlock(std::ifstream &fileStream) override;

    public:
    LevelOne();
    
};

#endif
