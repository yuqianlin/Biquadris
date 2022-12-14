#ifndef GRAPHICOBSERVER_H
#define GRAPHICOBSERVER_H

#include "observer.h"
#include "game.h"
#include <memory>
class Xwindow;

class GraphicObserver: public Observer {
    Game *subject;
    std::unique_ptr<Xwindow>uniqueWindow;
    Xwindow *window;
    int board_width;
    int board_height;
    int block_size;
    public:
        GraphicObserver(Game *g);
        void drawTile(int board, int row, int col, char type);
        void notify() override;
        ~GraphicObserver();
};

#endif
