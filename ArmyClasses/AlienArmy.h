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

    // Counts needed for the outputfile statistics

    // Initial units count
    int AScount;
    int AMcount;
    int ADcount;

    bool dronesToggler;

public:
    AlienArmy();

    void addUnit(Unit*);
    Unit* removeUnit(UnitType);
    void printArmy() const;
    void attack();
    bool isDead();

    // Getters
    int getUnitsCount(UnitType) const;
    int getDeadUnitsCount(UnitType) const;

    ~AlienArmy();


};

#endif