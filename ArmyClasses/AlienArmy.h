#ifndef ALIEN_ARMY_H
#define ALIEN_ARMY_H

#include "Army.h"
#include "..\Containers\LinkedQueue.h"
#include "..\Containers\Array.h"
#include "..\Containers\Deque.h"
#include "..\UnitClasses\Unit.h"
#include "..\UnitClasses\AlienSoldier.h"
#include "..\UnitClasses\AlienMonster.h"
#include "..\UnitClasses\AlienDrone.h"

class AlienArmy: public Army
{
private:
    LinkedQueue<Unit*> soldiers;
    Array<Unit*> monsters;
    Deque<Unit*> drones;

    bool dronesToggler;

public:
    AlienArmy();

    void addUnit(Unit*);
    Unit* removeUnit(UnitType);
    Unit* pickAttacker(UnitType);
    void printArmy() const;
    bool attack();
    bool isDead() const;

    // Getters
    int getUnitsCount(UnitType) const;

    ~AlienArmy();
};

#endif