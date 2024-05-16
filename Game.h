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

    LinkedQueue<Unit*> attackers; // Attackers of the current time step
    LinkedQueue<std::string> foughtUnits; // Units attacked by each attacker in the current timestep
    LinkedQueue<std::string> attackActions; // Action done on the unit of the opposite army

    LinkedQueue<Unit*> killedList;
    PriorityQueue<HealableUnit*> unitMaintenanceList;

private:
    bool startAttack(); // Makes the two armies attack each other
    void setGameMode(GameMode); // Change the game mode
    bool battleOver(bool) const; // Check if the battle is over
    void killSaverUnits(); // Savers need to be killed once all infected units are healed

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

    bool loadParameters(const std::string&); // Load the parameters from the file and sets parameters in the random generator

public:
    Game();

    void run(GameMode, const std::string&, const std::string&); // Run the game

    void addUnit(Unit*); // Add a unit to the appropriate army and list
    Unit* removeUnit(ArmyType, UnitType); // Remove a unit from the appropriate army and list
    LinkedQueue<Unit*> getEnemyList(ArmyType, UnitType, int); // Get the enemy list for the given army type, unit type and attack capacity
    void registerAttack(Unit*, const std::string&, const std::string&); // Store the current attacker along with its fought units

    void addToKilledList(Unit*); // Add a unit to the killed list

    void addUnitToMaintenanceList(HealableUnit*); // Add a unit to the maintenance list
    LinkedQueue<HealableUnit*> getUnitsToMaintainList(int); // Get a list of units that need to be maintained

    bool doesEarthNeedHelp() const; // Check if the Earth army needs help from the Earth Allied army if the number of infected units exceeds the threshold

    // Getters
    int getCurrentTimestep() const;
    int getUnitsCount(ArmyType, UnitType) const;
    int getInfectedUnitsCount() const;

    ~Game();
};

#endif