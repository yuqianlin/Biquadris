#include "command.h"
#include <string>
#include <iostream>
#include <utility>
#include <map>
#include "board.h"
#include "block.h"
using namespace std;

map<string, string> functionMap = {
    {"left", "leftF"},
    {"levelup", "levelUpF"},
    {"leveldown", "levelDownF"},
    {"right", "rightF"},
    {"random", "randomF"},
    {"restart", "restartF"},
    {"down", "downF"},
    {"drop", "dropF"},
    {"clockwise", "CWF"},
    {"counterclockwise", "CCWF"},
    {"norandom", "norandomF"},
    {"sequence", "sequenceF"},
    {"hint", "hintF"},
    {"I", "IF"},
    {"J", "JF"},
    {"L", "LF"},
    {"O", "OF"},
    {"Z", "ZF"},
    {"S", "SF"},
    {"T", "TF"},
    {"heavy", "heavyF"},
    {"blind", "blindF"},
    {"force", "forceF"},
};

Command::Command(string cmd) : //game{game}, 
cmd{cmd}, commandStart{0} {}

Command::~Command() {};

int Command::getMultiplier(string cmd, int &commandStart) {
    int multiplier = 0;
    for (size_t i = 0; i < cmd.size(); i++) {
        if (cmd[i] >= '0' && cmd[i] <= '9') {
            multiplier *= 10;
            multiplier += (cmd[i] - '0');
            commandStart++;
        } else if (i == 0 && multiplier == 0) {
            multiplier++;
            break;
        }
    }
    return multiplier;
}

bool Command::hasMultiplier(string cmd) {
    if (cmd[0] >= '0' && cmd[0] <= '9') {
        return true;
    } else {
        return false;
    }
}

pair<string, int> Command::interpret(string cmd) {
    string command = "";
    string output = ""; //for testing without game functions
    int matchingCmdCount = 0;
    int multiplier = getMultiplier(cmd, commandStart);
    bool multiplierExists = hasMultiplier(cmd);
    map<string, string>::iterator it = functionMap.begin();
    command = cmd.substr(commandStart, (cmd.size()-commandStart));

    while (it != functionMap.end()) {
        if (it->first.find(command) != string::npos && it->first.find(command) == 0) {
            matchingCmdCount++;
            correspondingCmd = it->second;
        }
        it++;
    }

    if (matchingCmdCount == 1) {
        if (correspondingCmd == "leftF") {
            output = "left";
        } else if (correspondingCmd == "levelUpF") {
            output = "levelup";
        } else if (correspondingCmd == "levelDownF") {
            output = "leveldown";
        } else if (correspondingCmd == "rightF") {
            output = "right";
        } else if (correspondingCmd == "randomF") {
            output = "random";
        } else if (correspondingCmd == "restartF") {
            output = "restart";
        } else if (correspondingCmd == "downF") {
            output = "down";
        } else if (correspondingCmd == "dropF") {
            output = "drop";
        } else if (correspondingCmd == "CWF") {
            output = "clockwise";
        } else if (correspondingCmd == "CCWF") {
            output = "counterclockwise";
        } else if (correspondingCmd == "norandomF") {
            output = "norandom";
        } else if (correspondingCmd == "sequenceF") {
            output = "sequence";
        } else if (correspondingCmd == "hintF") {
            output = "hint";
        } else if (correspondingCmd == "IF") {
            output = "I";
        } else if (correspondingCmd == "JF") {
            output = "J";
        } else if (correspondingCmd == "LF") {
            output = "L";
        } else if (correspondingCmd == "OF") {
            output = "O";
        } else if (correspondingCmd == "SF") {
            output = "S";
        } else if (correspondingCmd == "ZF") {
            output = "Z";
        } else if (correspondingCmd == "TF") {
            output = "T";
        } else if (correspondingCmd == "heavyF") {
            output = "heavy";
        } else if (correspondingCmd == "blindF") {
            output = "blind";
        } else if (correspondingCmd == "forceF") {
            output = "force";
        }
    } 
    
    if (matchingCmdCount == 1) {
        if (multiplierExists == true && (correspondingCmd == "hintF" || correspondingCmd == "norandomF" || correspondingCmd == "restartF" || correspondingCmd == "randomF")) {
            throw logic_error("Invalid command!");
        } else {
            return make_pair(output, multiplier); //replace this with calling command on game
        }
    } else if (matchingCmdCount == 0) {
        throw logic_error("Invalid command!");
    } else {
        throw logic_error("Please specify your command");
    }
}

string Command::getCommand() {
    return correspondingCmd;
}
