#include "textObserver.h"
#include <iostream>
#include <iomanip>

TextObserver::TextObserver(Game *g): subject{g}, col_start{0}, col_end{11}, row_start{-3}, row_end{15}, spacing{7} {
        subject->attach(this);
    }

TextObserver::~TextObserver() {
    subject->detach(this);
}

void TextObserver::notify() {
    using namespace std;

    cout << "Level:" << setw(5) << subject->getLevel(1) << setw(spacing) << " " << "Level:" << setw(5) << subject->getLevel(2) << endl;
    cout << "Score:" << setw(5) << subject->getCurScore(1) << setw(spacing) << " " << "Score:" << setw(5) << subject->getCurScore(2) << endl;
    cout << "HiScore:" << setw(3) << subject->getHiScore(1) << setw(spacing) << " " << "HiScore:" << setw(3) << subject->getHiScore(2) << endl;
    cout << "-----------" << setw(spacing) << " " << "-----------" << endl;
    for (int i = row_start; i < row_end; ++i) {
        for (int j = col_start; j < col_end; ++j) {
            cout << subject->blockAt(1, j, i); // print all blocks from first board - NOTE: rows and cols mixed up
        }
        cout << setw(spacing) << " ";
        for (int j = col_start; j < col_end; ++j) {
            cout << subject->blockAt(2, j, i); // print all blocks from second board
        }
        cout << "" << endl; // next line
    }
    cout << "-----------" << setw(spacing) << " " << "-----------" << endl;
    cout << "Next:" << setw(6) << " " << setw(spacing) << " " << "Next:" << setw(6) << " " << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = col_start; j < col_end; ++j) {
            cout << subject->blockAt(1, j, i, true);
        }
        cout << setw(spacing) << " ";
        for (int j = col_start; j < col_end; ++j) {
            cout << subject->blockAt(2, j, i, true);
        }
        cout << "" << endl;
    }
}
