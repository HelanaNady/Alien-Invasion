#include <iostream>

#include "EarthArmy.h"
#include "../UnitClasses/Unit.h"

void EarthArmy::addUnit(Unit* unit)
{
    if (unit->getUnitType() == UnitType::ES)
        soldiers.enqueue(unit);
    else if (unit->getUnitType() == UnitType::ET)
        tanks.push(unit);
    else if (unit->getUnitType() == UnitType::EG)
        gunneries.enqueue(unit, unit->getHealth() + unit->getPower());
}

void EarthArmy::removeUnit()
{
}

void EarthArmy::print() const
{
    std::cout <<"Earth Army: "<< std::endl;

    soldiers.printList();
    std::cout<<std::endl;
    
    tanks.printList();
    std::cout<<std::endl;
    
    gunneries.printList();
    std::cout<<std::endl;
}

void EarthArmy::attack()
{
}
