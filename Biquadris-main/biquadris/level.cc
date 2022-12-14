#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include <iostream>
#include <fstream>
using namespace std;

//constructor
Level::Level(int curLevel, bool random, Board *currentBoard) :
curLevel{curLevel}, random{random}, currentBoard{currentBoard} {
    filename = "";
}
//destructor
Level::~Level() {
};

int Level::getLevel() {
    return curLevel;
}

void Level::setFile(string file) {
    filename = file;
}

char Level::readFile(ifstream &fileStream) {
    char c;
    if (fileStream >> c) {
        return c;
    } else {
        fileStream.clear();
        fileStream.seekg(0);
        fileStream >> c;
        return c;
    }
}

char Level::readNthChar(string fileName) {
    int index = currentBoard->getElementIndex();
    ifstream in(fileName);
    char c;
    for (int i = 0; i < index; i++) {
        in >> c;
    }
    if (!(in >> c)) {
        in.clear();
        in.seekg(0);
        in >> c;
        currentBoard->increaseElementIndex(0);
    }
    currentBoard->increaseElementIndex(1);
    return c;
}

void Level::attachBoard(Board *b) {
    currentBoard = b;
}

unique_ptr<Level>updateLevel(int level) {
    if (level == 0) {
        return make_unique<LevelZero>();
    } else if (level == 1) {
        return make_unique<LevelOne>();
    } else if (level == 2) {
        return make_unique<LevelTwo>();
    } else if (level == 3) {
        return make_unique<LevelThree>();
    } else {  // newLevel = 4
        return make_unique<LevelFour>();
    }
}

void Level::changeRandom(bool newRandom) {
    random = newRandom;
}

string Level::getFileName() {
    return filename;
}
