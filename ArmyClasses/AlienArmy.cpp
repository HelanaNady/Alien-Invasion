#include <iostream>

#include "AlienArmy.h"
#include "../UnitClasses/Unit.h"

void AlienArmy::addUnit(Unit* unit)
{
    if (unit->getUnitType() == UnitType::AS)
        soldiers.enqueue(unit);
    //else if (unit->getUnitType() == UnitType::AM)
        // add it to array
    else 
        drones.enqueue(unit);
}

void AlienArmy::removeUnit()
{
}

void AlienArmy::print() const
{
    std::cout << "Alien Army: " << std::endl;
    soldiers.printList();
    std::cout << std::endl;
    drones.printList();
    std::cout << std::endl;
}

void AlienArmy::attack()
{
}
