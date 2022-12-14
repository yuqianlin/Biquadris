#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>
//#include "abstractboard.h"

class Block;
class Level;

class Board {
    std::unique_ptr<Level>level;
    int score;
    int highScore;
    bool specialAction = false;
    bool blind = false;
    bool heavy = false;
    bool force = false;
    bool random = false;
    int count = 0;
    int elementIndex = 0;
    char forceBlock;
    char nextBlock;
    std::string fileName;
    std::ifstream &input;
    std::vector<std::unique_ptr<Block>> blocks;
    std::unique_ptr<Block>nextBlockObject;
    Block *currentBlock; 
    // override = is it checking current block too?, curBlockOverride/tmpCurrentBlock = check overlap with a different block
    bool noOverlap(std::vector<std::pair<int, int>> tmp, bool override = false, bool curBlockOverride = false, Block *tempCurrentBlock = nullptr);
    void setBlind();
    void unsetBlind();
public:
    Board(int level, int highScore, std::ifstream &input, Block *nextBlockObject = nullptr);
    ~Board();
    std::ifstream &getInput();
    void setUp();
    // override = getting for nextLine
    char getBlock(int row, int col, bool override = false) const;
    char readNextBlock(std::ifstream &input);
    void setNextBlock(char c);
    char getNextBlock();
    void replaceCurrentBlock(char c);
    void moveLeft();
    void moveRight();
    void moveDown();
    void rotateCW();
    void rotateCCW();
    void drop();
    bool droppedBlock();
    bool updateBlock(char c); // returns whether or not game can continue
    void setHeavy();
    void unsetHeavy();
    void setSpecialAction(std::string action, char type = 'Z');
    void levelUp();
    void levelDown();
    void setForce(char type);
    void resetBoard();
    void setFileName(std::string newName);
    void changeRandom(bool randomValue);
    bool checkClearedLine(); // returns whether or not 2+ lines were cleared
    int getCount();
    int getElementIndex();
    int getBoardLevel();
    int getScore();
    int getHighScore();
    void increaseCount();
    void increaseElementIndex(int index);
};

#endif
