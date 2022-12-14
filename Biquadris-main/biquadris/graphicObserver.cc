#include "window.h"
#include "graphicObserver.h"
#include <string.h>
#include <iostream>
using namespace std;

GraphicObserver::GraphicObserver(Game *g): subject{g}, board_width{110}, board_height{180}, block_size{15} {
        uniqueWindow = make_unique<Xwindow>();
        window = uniqueWindow.get();
        subject->attach(this);
    }

GraphicObserver::~GraphicObserver() {
    subject->detach(this);
}

void GraphicObserver::drawTile(int board, int row, int col, char type) {
    int x = 0;
    int y = row * (block_size + 1) + 110;

    // determines x coordinate
    if (board == 1) {
        x = col * (block_size + 1) + 50;
    } else if (board == 2) {
        x = col * (block_size + 1) + 280;
    }

    if (type == ' ') {
        window->fillRectangle(x, y, block_size, block_size, 1);
    } else if (type == 'I') {
        window->fillRectangle(x, y, block_size, block_size, 5);
    } else if (type == 'J') {
        window->fillRectangle(x, y, block_size, block_size, 4);
    } else if (type == 'L') {
        window->fillRectangle(x, y, block_size, block_size, 8);
    } else if (type == 'O') {
        window->fillRectangle(x, y, block_size, block_size, 6);
    } else if (type == 'S') {
        window->fillRectangle(x, y, block_size, block_size, 3);
    } else if (type == 'T') {
        window->fillRectangle(x, y, block_size, block_size, 7);
    } else if (type == 'Z') {
        window->fillRectangle(x, y, block_size, block_size, 2);
    } else if (type == '*') {
        window->fillRectangle(x, y, block_size, block_size, 9);
    } else {
        window->fillRectangle(x, y, block_size, block_size, 0);
    }
}

void GraphicObserver::notify() { // NEED TO OPTIMIZE THIS SO THAT ONLY THE BOARD THAT MOVED IS REDRAWN
    window->drawString(220, 10, "BIQUADRIS"); // title

    char type;

    // Board 1
    if (subject->getMove() == 1 || subject->getMove() == 0) {
        window->fillRectangle(50, 10, 200, 50, 0);
        window->drawString(50, 30, "Level: " + std::to_string(subject->getLevel(1)));
        window->drawString(150, 30, "Score: " + std::to_string(subject->getCurScore(1)));
        window->drawString(150, 50, "HiScore: " + std::to_string(subject->getHiScore(1)));
        for (int i = -3; i < 15; ++i) {
            for (int j = 0; j < 11; ++j) {
                type = subject->blockAt(1, j, i); // draws all blocks from first board - NOTE: rows and cols mixed up
                drawTile(1, i, j, type);
            }
        }
        window->drawString(50, 370, "Next: ");
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 11; ++j) {
                type = subject->blockAt(1, j, i, true);
                if (type != ' ') {
                    drawTile(1, i + 17, j, type);
                } else {
                    drawTile(1, i + 17, j, 'w'); // draws white tile
                }
            }
        }
    }

    // Board 2
    if (subject->getMove() == 2 || subject->getMove() == 0) {
        window->fillRectangle(280, 10, 200, 50, 0);
        window->drawString(280, 30, "Level: " + std::to_string(subject->getLevel(2)));
        window->drawString(380, 30, "Score: " + std::to_string(subject->getCurScore(2)));
        window->drawString(380, 50, "HiScore: " + std::to_string(subject->getHiScore(2)));
        for (int i = -3; i < 15; ++i) {
            for (int j = 0; j < 11; ++j) {
                type = subject->blockAt(2, j, i); // draws all blocks from second board - NOTE: rows and cols mixed up
                drawTile(2, i, j, type);
            }
        }
        window->drawString(280, 370, "Next: ");
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 11; ++j) {
                type = subject->blockAt(2, j, i, true);
                if (type != ' ') {
                    drawTile(2, i + 17, j, type);
                } else {
                    drawTile(2, i + 17, j, 'w'); // draws white tile instead
                }
            }
        }
    }
}
