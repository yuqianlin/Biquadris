#include "level.h"
#include "level1.h"

#include <cstdlib>
#include <iostream>
using namespace std;

LevelOne::LevelOne(): Level{1, true} {
}

char LevelOne::getNextBlock(ifstream &fileStream) {
    int random = 1 + (rand() % 12);
    if (random == 1) {
        return 'S';
    } else if (random == 2) {
        return 'Z';
    } else if (random == 3 || random == 4) {
        return 'I';
    } else if (random == 5 || random == 6) {
        return 'T';
    } else if (random == 7 || random == 8) {
        return 'O';
    } else if (random == 9 || random == 10) {
        return 'J';
    } else { // (random == 11 || random == 12)
        return 'L';
    }
}
