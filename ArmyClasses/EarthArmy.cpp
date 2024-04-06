#include <iostream>

#include "EarthArmy.h"
#include "../UnitClasses/Unit.h"

void EarthArmy::addUnit(Unit* unit)
{
    if (unit->getUnitType() == UnitType::ES)
        soldiers.enqueue(dynamic_cast<EarthSoldier*>(unit)); 
    else if (unit->getUnitType() == UnitType::ET)
        tanks.push(dynamic_cast<EarthTank*>(unit));
    else if (unit->getUnitType() == UnitType::EG)
        gunneries.enqueue(dynamic_cast<EarthGunnery*>(unit), unit->getHealth() + unit->getPower());
}

void EarthArmy::removeUnit()
{}

void EarthArmy::print() const
{}

void EarthArmy::attack()
{}