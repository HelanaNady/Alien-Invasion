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

    bool dronesAddingToggler; // Used for peeking the drones in the addUnit function (front or back)
    bool dronesRemovingToggler; // Used for peeking the drones in the removeUnit function (front or back)
    bool dronesPickingToggler; // Used for peeking the drones in the pickAttacker function (front or back)

private:
    Unit* pickAttacker(UnitType); // Pick an attacker from the army and return it

public:
    AlienArmy(Game*);

    void addUnit(Unit*); // Add a unit to the army
    Unit* removeUnit(UnitType); // Remove a unit from the army and return it

    bool attack(); // Attack the enemy army
    bool isDead() const; // Check if the army is dead

    void printArmy() const; // Print the army units

    // Getters
    int getUnitsCount(UnitType) const; // Get the count of a specific unit type

    ~AlienArmy();
};

#endif