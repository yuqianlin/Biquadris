#ifndef LEVEL_ZERO_H
#define LEVEL_ZERO_H
#include "level.h"

class LevelZero: public Level{
    private:
    char getNextBlock(std::ifstream &fileStream) override;

    public:
    LevelZero();
    
};

#endif
