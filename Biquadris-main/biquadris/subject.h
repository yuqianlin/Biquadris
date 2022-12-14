#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;
class Board;

class Subject {
    std::vector<Observer*> observers;
 public:
    void attach(Observer *o);
    void detach(Observer *o);
    void notifyObservers(bool textOnly);
    virtual int getLevel(int board) const = 0;
    virtual int getCurScore(int board) const = 0;
    virtual int getHiScore(int board) const = 0;
    virtual char getNextBlock(int board) const = 0;
    virtual char blockAt(int board, int col, int row, bool override) const = 0;
    virtual ~Subject() = default;
};

#endif
