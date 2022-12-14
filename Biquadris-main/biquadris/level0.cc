#include "level0.h"

using namespace std;

LevelZero::LevelZero(): Level{0, false} {}

char LevelZero::getNextBlock(ifstream &fileStream) {
    return readFile(fileStream);
}
