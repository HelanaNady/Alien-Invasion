#include <iostream>

#include "EarthArmy.h"
#include "../UnitClasses/Unit.h"

void EarthArmy::addUnit(Unit* unit)
{
    UnitType unitType = unit->getUnitType();

    switch (unitType)
    {
        case UnitType::ES:
            soldiers.enqueue(unit);
            break;

        case UnitType::ET:
            tanks.push(unit);
            break;

        case UnitType::EG:
            gunneries.enqueue(unit, unit->getHealth() + unit->getPower());
            break;
    }
}

Unit* EarthArmy::removeUnit(UnitType unitType)
{
    Unit* unit = nullptr;

    switch (unitType)
    {
        case UnitType::ES:
            soldiers.dequeue(unit);
            break;

        case UnitType::ET:
            tanks.pop(unit);
            break;

        case UnitType::EG:
            int dummyPri;
            gunneries.dequeue(unit, dummyPri);
            break;
    }

    return unit;
}

void EarthArmy::print() const
{
    std::cout << "============== Earth Army Alive Units ==============" << std::endl;
    std::cout << soldiers.getCount() << " ES [";
    soldiers.printList();
    std::cout << "]" << std::endl;

    std::cout << tanks.getCount() << " ET [";
    tanks.printList();
    std::cout << "]" << std::endl;

    std::cout << gunneries.getCount() << " EG [";
    gunneries.printList();
    std::cout << "]" << std::endl;
}

void EarthArmy::attack()
{}