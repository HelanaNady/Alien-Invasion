#include <iostream>

#include "AlienArmy.h"
#include "../UnitClasses/Unit.h"

void AlienArmy::addUnit(Unit* unit)
{
    if (unit->getUnitType() == UnitType::AS)
        soldiers.enqueue(dynamic_cast<AlienSoldier*>(unit)); 
    //else if (unit->getUnitType() == UnitType::AM)
        // add it to array
    else 
        drones.enqueue(dynamic_cast<AlienDrone*>(unit));
}

void AlienArmy::removeUnit()
{}

void AlienArmy::print() const
{}

void AlienArmy::attack()
{}
