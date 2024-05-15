#ifndef EARTH_ARMY_H
#define EARTH_ARMY_H

#include "Army.h"
#include "..\Containers\ArrayStack.h"
#include "..\Containers\LinkedQueue.h"
#include "..\Containers\PriorityQueue.h"
#include "..\UnitClasses\Unit.h"
#include "..\UnitClasses\EarthSoldier.h"
#include "..\UnitClasses\EarthTank.h"
#include "..\UnitClasses\EarthGunnery.h"
#include "..\UnitClasses\HealUnit.h"

class EarthArmy: public Army
{
private:
    enum { INFECTION_SPREAD_CHANCE = 2 }; // Chance to spread infection
    static int infectionThreshold; // Infection threshold for the army to need ally help

    LinkedQueue<Unit*> soldiers;
    ArrayStack<Unit*> tanks;
    PriorityQueue<Unit*> gunneries;
    ArrayStack<Unit*> healers;

    int infectedSoldiersCount; // Count of infected soldiers in the army

public:
    EarthArmy(Game*);

    // Static functions
    static void setInfectionThreshold(int); // Set the infection threshold for the army

    void addUnit(Unit*); // Add a unit to the army
    Unit* removeUnit(UnitType); // Remove a unit from the army and return it
    Unit* pickAttacker(UnitType); // Pick an attacker from the army and return it

    bool attack(); // Attack the enemy army
    bool isDead() const; // Check if the army is dead
    bool needAllyHelp() const; // Check if the army needs ally help

    void printArmy() const; // Print the army units

    void killHealUnit(); // Kill a healer unit
    void spreadInfection(); // Spread infection to the army

    // Getters
    int getUnitsCount(UnitType) const; // Get the count of a specific unit type
    float getInfectionPercentage() const; // Get the infection percentage of the army
    int getInfectedSoldiersCount() const; // Get the infected soldiers count

    ~EarthArmy();
};

#endif