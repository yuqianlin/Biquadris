#include "level3.h"
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

LevelThree::LevelThree(): Level{3, true} {}

char LevelThree::getNextBlock(ifstream &fileStream) {
    int random = 1 + (rand() % 9);
    if (this->random == false) {
        string file = this->getFileName();
        return readNthChar(file);
    } else {
        if (random == 1 || random == 2) {
            return 'S';
        } else if (random == 3 || random == 4) {
            return 'Z';
        } else if (random == 5) {
            return 'I';
        } else if (random == 6) {
            return 'T';
        } else if (random == 7) {
            return 'O';
        } else if (random == 8) {
            return 'J';
        } else { //  (random == 9) {
            return 'L';
        }
    }
}
