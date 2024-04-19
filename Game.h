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

    LinkedQueue<Unit*> killedList; // Queue of killed units

private:
    void incrementTimestep(); // Increment the current timestep by 1 and process the timestep
    void changeGameMode(GameMode); // Change the game mode
    bool battleOver() const; // Check if the battle is over (current timestep >= 50)

    void printAll() const; // Prints all the armies and the killed list
    void printKilledList() const; // Prints the killed list

    void loadParameters(std::string); // Load the parameters from the file and sets parameters in the random generator

public:
    Game();

    void run(GameMode, std::string); // Run the game

    void addUnit(Unit*); // Add a unit to the appropriate army and list
    void addToKilledList(Unit*); // Add a unit to the killed list

    // Getters
    int getCurrentTimestep() const;

    ~Game();
};

#endif