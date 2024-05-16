#ifndef ARMY_H
#define ARMY_H

#include "../UnitClasses/Unit.h"

class Game;

class Army
{
protected:
    Game* gamePtr;
    LinkedQueue<Unit*> currentAttackers; // The units that are currently attacking the enemy army (used for printing)

private:
    virtual Unit* pickAttacker(UnitType) = 0; // Pick an attacker from the army and return it

public:
    Army(Game*);

    virtual void addUnit(Unit*) = 0; // Add a unit to the army
    virtual Unit* removeUnit(UnitType) = 0; // Remove a unit from the army and return it

    virtual bool attack() = 0; // Attack the enemy army
    virtual bool isDead() const = 0; // Check if the army is dead

    virtual void printArmy() const = 0; // Print the army units

    // Getters
    virtual int getUnitsCount(UnitType) const = 0; // Get the count of a specific unit type
};

#endif