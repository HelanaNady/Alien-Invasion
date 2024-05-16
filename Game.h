#ifndef GAME_H
#define GAME_H

#include <string>

#include "DEFS.h"
#include "ArmyClasses/EarthArmy.h"
#include "ArmyClasses/AlienArmy.h"
#include "ArmyClasses/EarthAlliedArmy.h"
#include "RandomGenerator/RandomGenerator.h"
#include "Containers/LinkedQueue.h"
#include "Containers/PriorityQueue.h"
#include "Logger.h"
#include "UnitClasses/HealableUnit.h"

class Game
{
private:
    GameMode gameMode;
    int currentTimestep;

    EarthArmy earthArmy;
    AlienArmy alienArmy;
    EarthAlliedArmy earthAlliedArmy;
    RandomGenerator randomGenerator;

    LinkedQueue<Unit*> killedList;
    PriorityQueue<HealableUnit*> unitMaintenanceList;

    // Logger
    Logger logger;

private:
    bool startAttack(); // Makes the two armies attack each other
    void setGameMode(GameMode); // Change the game mode
    bool battleOver(bool) const; // Check if the battle is over
    bool areUnitsFighting() const; // Check if there are units fighting

    void printKilledList() const; // Prints the killed list with the console formats
    void printUnitMaintenanceList() const; // Print the units at the maintence list
    void printAll(); // Prints all the armies and the killed list and units fighting at the current timestep

    std::string battleResult() const; // Returns the result of the battle
    void printFinalResults() const; // Print the final results of the game

    void emptyUnitMaintenanceList(); // Empty the unit maintenance list by killing all units in it

    GameStatistics countStatistics(); // Calculate the statistics of the game
    void countArmyStatistics(GameStatistics&, ArmyType, UnitType[], int); // Count the statistics of the given army
    void countKilledUnitsStatistics(GameStatistics&); // Count the statistics of the killed units
    void generateOutputFile(const std::string&); // Generate the output file with the statistics

    bool loadParameters(std::string); // Load the parameters from the file and sets parameters in the random generator

public:
    Game();

    std::string gameModeToString(GameMode);  // Convert the game mode to string
    void run(GameMode, std::string, std::string);  // Run the game

    void addUnit(Unit*);  // Add a unit to the appropriate army and list
    Unit* removeUnit(ArmyType, UnitType);  // Remove a unit from the appropriate army and list
    LinkedQueue<Unit*> getEnemyList(ArmyType, UnitType, int); // Get the enemy list for the given army type, unit type and attack capacity

    void addToKilledList(Unit*);  // Add a unit to the killed list

    void addUnitToMaintenanceList(HealableUnit*); // Add a unit to the maintenance list
    LinkedQueue<HealableUnit*> getUnitsToMaintainList(int);

    bool doesEarthNeedHelp() const; // A check for the infection perecentage for saver units generation
    void killSaverUnits(); // Savers need to be killed once all infected units are healed

    void logStartOfGame();
    void logBeginOfTimeStep();
    void log(std::string);
    void logEndOfTimeStep();
    void logEndOfGame();

    // Getters
    int getCurrentTimestep() const;
    int getUnitsCount(ArmyType, UnitType) const;
    int getInfectedUnitsCount() const;

    ~Game();
};

#endif