#ifndef LEVEL_THREE_H
#define LEVEL_THREE_H

#include "level.h"
#include "block.h"
#include <string>
class LevelThree: public Level{
    private:
    char getNextBlock(std::ifstream &fileStream) override;

    public:
    LevelThree();
    
};

#endif
