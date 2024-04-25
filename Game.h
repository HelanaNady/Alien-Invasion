#ifndef GAME_H
#define GAME_H

#include <string>

#include "DEFS.h"
#include "ArmyClasses/EarthArmy.h"
#include "ArmyClasses/AlienArmy.h"
#include "RandomGenerator/RandomGenerator.h"
#include "Containers/LinkedQueue.h"
#include "Containers/PriorityQueue.h"

class Game
{
private:
    GameMode gameMode;
    int currentTimestep;

    EarthArmy earthArmy;
    AlienArmy alienArmy;
    RandomGenerator randomGenerator;

    LinkedQueue<Unit*> killedList;
    PriorityQueue<Unit*> unitMaintenanceList;

private:
    bool startAttack(); // Makes the two armies attack each other
    void setGameMode(GameMode); // Change the game mode
    bool battleOver(bool); // Check if the battle is over
    std::string battleResult();

    void printKilledList() const; // Prints the killed list with the console formats
    void printUnitMaintenanceList() const; // Print the units at the maintence list
    void printAll(); // Prints all the armies and the killed list and units fighting at the current timestep

    GameStatistics countStatistics(); // Calculate the statistics of the game
    void printOutputFile(std::string); // Print the output file

    bool loadParameters(std::string); // Load the parameters from the file and sets parameters in the random generator

public:
    Game();

    void run(GameMode, std::string, std::string);  // Run the game

    void addUnit(Unit*);  // Add a unit to the appropriate army and list
    void addToKilledList(Unit*);  // Add a unit to the killed list
    LinkedQueue<Unit*> getEnemyList(ArmyType, UnitType, int); // Get the enemy list for the given army type, unit type and attack capacity

    void addUnitToMaintenanceList(Unit*); // Add a unit to the maintenance list
    LinkedQueue<Unit*> getUnitsToMaintainList(int);

    // Getters
    int getCurrentTimestep() const;
    int getUnitsCount(ArmyType, UnitType) const;

    ~Game();
};

#endif