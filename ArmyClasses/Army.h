#ifndef ARMY_H
#define ARMY_H

#include "../UnitClasses/Unit.h"

class Army
{
protected:
    LinkedQueue<Unit*> currentFightors; // enqueue at the beginning of each attack function  
public:
    void printFightingUnits();
    virtual int getUnitsCount(UnitType) const = 0;
    virtual int getDeadUnitsCount(UnitType) const = 0;
    virtual void addUnit(Unit*) = 0;
    virtual Unit* removeUnit(UnitType) = 0;
    virtual void printArmy() const = 0;
    virtual void attack() = 0;
};

#endif