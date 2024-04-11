#ifndef ARMY_H
#define ARMY_H

#include "../UnitClasses/Unit.h"

class Army
{
public:
    virtual void addUnit(Unit*) = 0; // Add a unit to the army
    virtual Unit* removeUnit(UnitType) = 0; // Remove a unit from the army
    virtual void print() const = 0; // Print the army
    virtual void attack() = 0; // Picks a unit from each list and calls the attack function of the unit
};

#endif