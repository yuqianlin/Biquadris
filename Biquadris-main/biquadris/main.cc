#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "board.h"
#include "block.h"
#include "iblock.h"
#include "oblock.h"
#include "jblock.h"
#include "lblock.h"
#include "sblock.h"
#include "zblock.h"
#include "tblock.h"
#include "command.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "game.h"
#include "textObserver.h"
#include "graphicObserver.h"
#include "window.h"

using namespace std;

void checkCmdLineArgs(int argc, char **&argv, bool &textOnly, string &seq1, string &seq2, int &level, int &seed) {
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-text") {
            textOnly = true;
        } else if (arg == "-seed") {
            ++i;
            istringstream s{argv[i]};
            int newSeed;
            if (s >> newSeed) {
                seed = newSeed;
            } else {
                cout << "Invalid seed - must be an integer." << endl;
            }
        } else if (arg == "-scriptfile1") {
            ++i;
            seq1 = argv[i];
        } else if (arg == "-scriptfile2") {
            ++i;
            seq2 = argv[i];
        } else if (arg == "-startlevel") {
            ++i;
            istringstream s{argv[i]};
            int newLevel;
            if (s >> newLevel && 0 <= newLevel && newLevel <= 4) {
                level = newLevel;
            } else {
                cout << "Invalid level - must be number between 0 and 4." << endl;
            }
        } else {
            cout << "Invalid command line argument." << endl;
        }
    }
}

int main(int argc, char **argv) {
    bool textOnly = false;
    int level = 0;
    int seed = 1;

    string seq1 = "biquadris_sequence1.txt";
    string seq2 = "biquadris_sequence2.txt";
    checkCmdLineArgs(argc, argv, textOnly, seq1, seq2, level, seed);
    unique_ptr<Level>l1 = updateLevel(level);
    unique_ptr<Level>l2 = updateLevel(level);
    srand(seed);
    ifstream input1{seq1};
    ifstream input2{seq2};
    unique_ptr<Game>g(new Game{input1, input2, level, textOnly, cin});
    unique_ptr<TextObserver>text(new TextObserver{g.get()});
    unique_ptr<GraphicObserver>graphic = nullptr;
    if (!textOnly) {
        graphic.reset(new GraphicObserver{g.get()});
    }
    g->run(cin);
    cout << "Thank you for playing!" << endl;
}
