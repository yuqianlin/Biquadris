#ifndef COMMAND_H
#define COMMAND_H

#include "game.h"
#include <string>
#include <utility>

class Command{
    private:
    //Game *game;
    std::string cmd;
    int commandStart;
    std::string correspondingCmd;
    //map<string, string> functionMap;

    int getMultiplier(std::string cmd, int &commandStart);
    bool hasMultiplier(std::string cmd);

    public:
    explicit Command(std::string translateCmd);
    std::string getCommand();
    ~Command();
    std::pair<std::string, int> interpret(std::string cmd);
};
#endif
