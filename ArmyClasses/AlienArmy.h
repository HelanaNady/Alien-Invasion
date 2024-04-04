#ifndef ALIEN_ARMY_H
#define ALIEN_ARMY_H

#include "Army.h"
#include "..\Containers\LinkedQueue.h"
#include "..\Containers\ArrayStack.h"
#include "..\Containers\Deque.h"
#include "..\UnitClasses\Unit.h"
#include "..\UnitClasses\AlienSoldier.h"
#include "..\UnitClasses\AlienMonster.h"
#include "..\UnitClasses\AlienDrone.h"

class AlienArmy: public Army
{
private:
    LinkedQueue<AlienSoldier*> soldiers;
    // Array <AlienMonster> monsters;
    Deque<AlienDrone*> drones;

public:
    void addUnit();
    void removeUnit();
    void print() const;
    void attack();
};

#endif