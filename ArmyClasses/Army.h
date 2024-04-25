#ifndef ARMY_H
#define ARMY_H

#include "../UnitClasses/Unit.h"

class Army
{
protected:
    LinkedQueue<Unit*> currentAttackers; // enqueue at the beginning of each attack function  
public:
    virtual void addUnit(Unit*) = 0;
    virtual Unit* removeUnit(UnitType) = 0;
    virtual Unit* pickAttacker(UnitType) = 0;
    virtual bool attack() = 0;
    virtual bool isDead() const = 0;

    virtual int getUnitsCount(UnitType) const = 0;
    virtual void printArmy() const = 0;
    void printFightingUnits();
};

#endif