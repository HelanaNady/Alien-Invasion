#ifndef GAME_LOGGER_H
#define GAME_LOGGER_H

#include <fstream>
#include <string>

class Game;

class Logger
{
private:
    Game* gamePtr; // Pointer to the game object
    std::ofstream logFile; // File stream for the log file
    int latestTimestep; // The latest timestep logged

public:
    Logger(Game*, const std::string);

    void log(std::string);
    void addBreakLine();

    ~Logger();
};

#endif