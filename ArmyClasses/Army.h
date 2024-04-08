#ifndef ARMY_H
#define ARMY_H

#include "../UnitClasses/Unit.h"

class Army
{
public:
    virtual void addUnit(Unit*) = 0;
    virtual Unit* removeUnit(UnitType) = 0;
    virtual void printArmy() const = 0;
    virtual void attack() = 0;
};

#endif