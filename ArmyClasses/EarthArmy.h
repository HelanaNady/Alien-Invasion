#ifndef EARTH_ARMY_H
#define EARTH_ARMY_H

#include "Army.h"
#include "..\UnitClasses\Unit.h"
#include "..\Containers\ArrayStack.h"
#include "..\Containers\LinkedQueue.h"
#include "..\Containers\PriorityQueue.h"
#include "..\UnitClasses\Unit.h"
#include "..\UnitClasses\EarthSoldier.h"
#include "..\UnitClasses\EarthTank.h"
#include "..\UnitClasses\EarthGunnery.h"

class EarthArmy: public Army
{
private:
    LinkedQueue<EarthSoldier*> soldiers;
    ArrayStack<EarthTank*> tanks;
    PriorityQueue<EarthGunnery*> gunneries;

public:
    void addUnit();
    void removeUnit();
    void print() const;
    void attack();
};

#endif
