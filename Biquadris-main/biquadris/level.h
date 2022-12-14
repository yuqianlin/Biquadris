#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "block.h"
#include "board.h"
#include <iostream>
#include <fstream>

class Level {
    protected:
        int curLevel;
        bool random;
        Board* currentBoard;
        std::string filename;
    public:
        Level(int curLevel, bool random, Board *currentBoard = nullptr);
        int getLevel();
        virtual char getNextBlock(std::ifstream &fileStream) = 0;
        char readFile(std::ifstream &fileStream);
        char readNthChar(std::string fileName);
        void setFile(std::string file);
        void attachBoard(Board *b);
        void changeRandom(bool newRandom);
        std::string getFileName();
        virtual ~Level() = 0;
};

std::unique_ptr<Level> updateLevel(int level);

#endif
