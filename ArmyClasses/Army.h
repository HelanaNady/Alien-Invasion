#ifndef ARMY_H
#define ARMY_H

#include "../UnitClasses/Unit.h"

class Game;

class Army
{
protected:
    Game* gamePtr;
    LinkedQueue<Unit*> currentAttackers; // enqueue at the beginning of each attack function  
public:
    Army(Game*);

    virtual void addUnit(Unit*) = 0;
    virtual Unit* removeUnit(UnitType) = 0;
    virtual Unit* pickAttacker(UnitType) = 0;
    virtual void attack() = 0;
    virtual bool isDead() const = 0;

    virtual int getUnitsCount(UnitType) const = 0;
    virtual void printArmy() const = 0;
    void printFightingUnits();
};

#endif