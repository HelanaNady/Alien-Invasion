#ifndef GAME_H
#define GAME_H

#include <string>

#include "DEFS.h"
#include "ArmyClasses/EarthArmy.h"
#include "ArmyClasses/AlienArmy.h"
#include "RandomGenerator/RandomGenerator.h"
#include "Containers/LinkedQueue.h"

class Game
{
private:
    GameMode gameMode;
    int currentTimestep;

    EarthArmy earthArmy;
    AlienArmy alienArmy;
    RandomGenerator* randomGenerator;

    LinkedQueue<Unit*> killedList;

public:
    Game();

    void run(GameMode, std::string);
    void incrementTimestep();
    void changeGameMode(GameMode);
    bool battleOver() const;
    void addUnit(Unit*);
    void killUnit(Unit*);
    void printKilledList() const;

    std::string loadFromFile(std::string);

    // Getters
    int getCurrentTimestep() const;

    ~Game();
};

#endif