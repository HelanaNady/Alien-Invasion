#ifndef GAME_H
#define GAME_H

#include "ArmyClasses/EarthArmy.h"
#include "ArmyClasses/AlienArmy.h"
#include "RandomGenerator/RandomGenerator.h"
#include "Containers/LinkedQueue.h"

#include <string>

enum GameMode
{
    INTERACTIVE,
    SILENT,
};

class Game
{
private:
    GameMode gameMode;
    int currentTimestep;

    EarthArmy earthArmy;
    AlienArmy alienArmy;
    RandomGenerator* randomGenerator;

    LinkedQueue<Unit*> killedList;

private:
    std::string loadFile(std::string fileName);

public:
    Game();

    void run(GameMode, std::string);
    void incrementTimestep();
    void changeGameMode(GameMode);
    bool battleOver() const;
    void addUnit(Unit*);
    void killUnit(Unit*);
    void printKilledList() const;

    // Getters
    int getCurrentTimestep() const;

    ~Game();
};

#endif