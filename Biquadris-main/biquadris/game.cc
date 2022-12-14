#include "game.h"
#include "command.h"
#include "board.h"
#include "block.h"
#include "level.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Game::Game(ifstream &input1, ifstream &input2, int level, bool textOnly, istream &in): textOnly{textOnly}, in{in}
{
    board1 = make_unique<Board>(level, 0, input1);
    board2 = make_unique<Board>(level, 0, input2);
} 

Game::~Game() {}

bool Game::getP1Turn() {
    return p1Turn;
}

void Game::toggleP1Turn() {
    if (p1Turn) {
        p1Turn = false;
    } else {
        p1Turn = true;
    }
}

void Game::restartGame() {
    board1->resetBoard();
    board2->resetBoard();
}

void Game::endGame() {
    // what to do when game ends?
}
void Game::render() { // TODO: figure out what render should do
    notifyObservers(textOnly);
}

int Game::getLevel(int board) const {
    if (board == 1) {
        return board1->getBoardLevel();
    }
    return board2->getBoardLevel();
}

int Game::getCurScore(int board) const {
    if (board == 1) {
        return board1->getScore();
    }
    return board2->getScore();
}
int Game::getHiScore(int board) const {
    if (board == 1) {
        return board1->getHighScore();
    }
    return board2->getHighScore(); // or some value like this
}
char Game::getNextBlock(int board) const {
    if (board == 1) {
        return board1->getNextBlock();
    }
    return board2->getNextBlock();
}

char Game::blockAt(int board, int row, int col, bool override) const {
    if (board == 1) {
        return board1->getBlock(row, col, override);
    }
    return board2->getBlock(row, col, override);
}

void Game::triggerSpecialAction(Board &b) {
    string action;
    cout << "Special action triggered! Please enter your special action: " << endl;
    cin >> action;
    if (action == "blind") {
        b.setSpecialAction(action);
    } else if (action == "heavy") {
        b.setSpecialAction(action);
    } else if (action == "force") {
        char type;
        cin >> type;
        b.setSpecialAction(action, type);
    } else {
        cout << "Invalid special action." << endl;
    }
}

int Game::getMove() {
    return moveMade;
}

bool Game::makeMove(pair<string, int>c, ifstream &input) {
    Board *b;
    if (p1Turn) {
        b = board1.get();
        moveMade = 1;
    } else {
        b = board2.get();
        moveMade = 2;
    }
    string s = c.first;
    for (int i = 0; i < c.second; ++i) {
        if (s == "left") {
            b->moveLeft();
        } else if (s == "right") {
            b->moveRight();
        } else if (s == "down") {
            b->moveDown();
        } else if (s == "drop") {
            b->drop();
            b->increaseCount();
        } else if (s == "counterclockwise") {
            b->rotateCCW();
        } else if (s == "clockwise") {
            b->rotateCW();
        } else if (s == "blind") {
            b->setSpecialAction(s);
        } else if (s == "heavy") {
            b->setSpecialAction(s);
        } else if (s == "force") {
            char type;
            in >> type;
            b->setSpecialAction(s, type);
        } else if (s == "levelup") {
            if (b->getBoardLevel() == 4) {
                cout << "Invalid level - must be number between 0 and 4." << endl;
            }         
            b->levelUp();   
        } else if (s == "leveldown") {
            if (b->getBoardLevel() == 0) {
                cout << "Invalid level - must be number between 0 and 4." << endl;
            } 
            b->levelDown();
        } else if (s == "sequence") {
            string file;
            if (in >> file) {
                ifstream fileSequence{file};
                run(fileSequence);
            } else {
                cout << "Invalid sequence file." << endl;
            }
        } else if (s == "restart") {
            restartGame();
            moveMade = 0;
        } else if (s == "I" || s == "L" || s == "J" || s == "S" || s == "Z" || s == "T" || s == "O") {
            istringstream str{s};
            char c;
            str >> c;
            b->replaceCurrentBlock(c);
        } else if (s == "norandom") {
            b->changeRandom(false);
            string file;
            if (in >> file) {
                b->setFileName(file);
            } else {
                cout << "Invalid noRandom file." << endl;
            }
        } else if (s == "random") {
            b->changeRandom(true);
            b->setFileName("");
        } else {
            cout << "Invalid command." << endl;
        }
        if (b->droppedBlock()) {
            bool twoOrMore = b->checkClearedLine();
            char c;
            if (b->getBoardLevel() == 4 && b->getCount() > 0 && b->getCount() % 5 == 0) {
                bool safeToContinue = b->updateBlock('*');
                if (!safeToContinue) {
                    return false;
                }
                b->drop();
            } 
            c = b->readNextBlock(input);
            bool safeToContinue = b->updateBlock(b->getNextBlock());
            if (!safeToContinue) {
                return false;
            }
            b->setNextBlock(c);
            if (twoOrMore) {
                render();
                if (p1Turn) {
                    triggerSpecialAction(*board2);
                } else {
                    triggerSpecialAction(*board1);
                }
            }
            toggleP1Turn();
        }
    }
    return true;
}

pair<string, int> Game::interpretCommand(string cmd) {
    Command c{cmd};
    try {
        return c.interpret(cmd);
    } catch (logic_error &e) {
        throw;
    }
}

bool Game::runCommand(string command) {
    Board *b;
    if (p1Turn) {
        b = board1.get();
    } else {
        b = board2.get();
    }
    try {
        pair<string, int> c = interpretCommand(command);
        if (!makeMove(c, b->getInput())) {
            cout << "You lost! :(" << endl;
            return true;
        }
    } catch (logic_error &e) {
        cout << e.what() << endl;
    }
    return false;
}

void Game::run(istream &in) {
    bool gameOver = false;
    while (!gameOver) {
        render();
        string command;
        if (in >> command) {
            gameOver = runCommand(command);
        } else {
            gameOver = true;
        }
    }
}
