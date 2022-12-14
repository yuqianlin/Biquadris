#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include "subject.h"

class Board;
class Level;

class Game: public Subject {
    std::unique_ptr<Board>board1;
    std::unique_ptr<Board>board2;
    bool p1Turn = true;
    bool textOnly = false;
    int moveMade = 0; // 0 for both boards, 1 for board1 making a move, 2 for board2 making a move
    public:
        Game(std::ifstream &input1, std::ifstream &input2, int level, bool textOnly, std::istream &in); // construct a game
        std::istream &in;
        void restartGame();
        void endGame();
        void render(); // calls notifyObservers in Subject class everytime a move is made
        int getLevel(int board) const override;
        int getCurScore(int board) const override;
        int getHiScore(int board) const override;
        char getNextBlock(int board) const override;
        char blockAt(int board, int row, int col, bool override = false) const override;
        int getMove();
        bool getP1Turn();
        void toggleP1Turn();
        void triggerSpecialAction(Board &b);
        bool makeMove(std::pair<std::string, int>c, std::ifstream &input);
        std::pair<std::string, int> interpretCommand(std::string cmd);
        bool runCommand(std::string cmd);
        void run(std::istream &in);
        ~Game();
};

#endif
