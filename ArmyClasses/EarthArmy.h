#ifndef EARTH_ARMY_H
#define EARTH_ARMY_H

#include "Army.h"
#include "..\Containers\ArrayStack.h"
#include "..\Containers\LinkedQueue.h"
#include "..\Containers\PriorityQueue.h"
#include "..\UnitClasses\Unit.h"
#include "..\UnitClasses\EarthSoldier.h"
#include "..\UnitClasses\EarthTank.h"
#include "..\UnitClasses\EarthGunnery.h"
#include "..\UnitClasses\HealUnit.h"

class EarthArmy: public Army
{
private:
    enum { INFECTION_SPREAD_CHANCE = 2 }; // Chance to spread infection
    static int infectionThreshold;

    LinkedQueue<Unit*> soldiers;
    ArrayStack<Unit*> tanks;
    PriorityQueue<Unit*> gunneries;
    ArrayStack<Unit*> healers;

    int infectedSoldiersCount;

public:
    EarthArmy(Game*);

    void addUnit(Unit*);
    Unit* removeUnit(UnitType);
    Unit* pickAttacker(UnitType);
    void printArmy() const;
    bool attack();
    bool isDead() const;
    void killHealUnit();

    // Infection functions
    void incrementInfectedSoldiersCount();
    void spreadInfection();

    bool needAllyHelp() const;

    // Getters
    int getUnitsCount(UnitType) const;

    // Static functions
    static void setInfectionThreshold(int);

    ~EarthArmy();
};

#endif