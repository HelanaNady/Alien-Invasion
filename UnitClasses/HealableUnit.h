#ifndef HEALABLE_UNIT_H
#define HEALABLE_UNIT_H

#include "Unit.h"
#include "../DEFS.h"

class HealableUnit: public Unit
{
protected:
    int UMLjoinTime; // Time when the unit joined the UML
    bool healedBefore; // Check if the unit has been healed before

public:
    HealableUnit(Game*, UnitType, double, int, int);

    virtual int getHealPriority() const = 0; // Get the heal priority of the unit varies from one unit to another

    bool needsHeal() const; // Check if the unit is eligible for healing
    bool hasWaitedForTooLong() const; // Decides whether to kill or heal the unit based on its wait time
    bool isHealed() const; // Checks if the unit's health has increased enough
    bool hasBeenInUMLbefore() const; // Check if it has been inside uml before or not
    bool hasBeenHealedBefore() const; // Check if the unit has been healed before or not

    void receiveHeal(double); // Increase the health of the unit by "UHP"

    // Setters
    void setUMLjoinTime(int); // Set the time when the unit joined the UML
};

#endif