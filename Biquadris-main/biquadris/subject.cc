#include "subject.h"
#include "observer.h"
#include "game.h"

void Subject::attach(Observer *o) {
    observers.emplace_back(o);
}

void Subject::detach(Observer *o) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            break;
        }
    }
}

void Subject::notifyObservers(bool textOnly) {
    if (textOnly) { // if textOnly is true, only notify text observer (assumes text is first observer)
        observers.front()->notify();
        return;
    }
    for (auto ob:observers) {
        ob->notify();
    }
}
