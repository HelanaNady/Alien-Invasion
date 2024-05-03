#ifndef HEALABLE_UNIT_H
#define HEALABLE_UNIT_H

#include "Unit.h"
#include "../DEFS.h"

class HealableUnit: public Unit
{
protected:
    int UMLjoinTime; // Time when the unit joined the UML

public:
    HealableUnit(Game*, UnitType, double, int, int);

    virtual bool needsHeal() const; // Check if the unit is eligible for healing

    virtual int getHealPriority() const = 0;  // Get the heal priority of the soldier to be used in the UML

    void receiveHeal(double); // Increase the health of the unit by "UHP"

    int getUMLjoinTime() const; // Get the time when the unit joined the UML
    void setUMLjoinTime(int); // Set the time when the unit joined the UML
    bool hasWaitedForTooLong() const; // Decides whether to kill or heal the unit based on its wait time
    bool isHealed() const; // Checks if the unit's health has increased enough
};

#endif