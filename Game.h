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
    RandomGenerator randomGenerator;

    LinkedQueue<Unit*> killedList;

private:
    void incrementTimestep();  // Increment the current timestep by 1 and process the timestep
    void setGameMode(GameMode); // Change the game mode
    bool battleOver(); // Check if the battle is over

    void printAll(); // Prints all the armies and the killed list and units fighting at the current timestep
    void printKilledList() const; // Prints the killed list with the console formats

    bool loadParameters(std::string); // Load the parameters from the file and sets parameters in the random generator

public:
    Game();

    void run(GameMode, std::string);  // Run the game

    void addUnit(Unit*);  // Add a unit to the appropriate army and list
    void addToKilledList(Unit*);  // Add a unit to the killed list
    LinkedQueue<Unit*> getEnemyList(ArmyType, UnitType, int); // Get the enemy list for the given army type, unit type and attack capacity

    // Getters
    int getCurrentTimestep() const;
    int getUnitsCount(ArmyType, UnitType) const;

    ~Game();
};

#endif