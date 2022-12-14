#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H

#include "observer.h"
#include "game.h"

class TextObserver: public Observer {
    Game *subject;
    int col_start;
    int col_end;
    int row_start;
    int row_end;
    int spacing;
    public:
        TextObserver(Game *g);
        void notify() override;
        ~TextObserver();
};

#endif
