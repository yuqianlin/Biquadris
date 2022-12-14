#include "level2.h"

#include <cstdlib>
#include <iostream>
using namespace std;

LevelTwo::LevelTwo(): Level{2, true} {}

char LevelTwo::getNextBlock(ifstream &fileStream) {
    int random = 1 + (rand() % 7);
    if (random == 1) {
        return 'S';
    } else if (random == 2) {
        return 'Z';
    } else if (random == 3) {
        return 'I';
    } else if (random == 4) {
        return 'T';
    } else if (random == 5) {
        return 'O';
    } else if (random == 6) {
        return 'J';
    } else { // (random == 7)
        return 'L';
    }
}
