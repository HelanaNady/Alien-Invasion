#include <iostream>

#include "EarthArmy.h"
#include "../UnitClasses/Unit.h"


EarthArmy::EarthArmy(): EScount(0), EGcount(0), ETcount(0), deadEScount(0), deadEGcount(0), deadETcount(0)
{
}

void EarthArmy::addUnit(Unit* unit)
{
    UnitType unitType = unit->getUnitType();

    switch (unitType)
    {
        case UnitType::ES:
            soldiers.enqueue(unit);
            EScount++;
            break;
       
        case UnitType::ET:
            tanks.push(unit);
            ETcount++;
            break;

        case UnitType::EG:
            gunneries.enqueue(unit, unit->getHealth() + unit->getPower());
            EGcount++;
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

int EarthArmy::getUnitsCount(UnitType unitType) const
{
    switch (unitType)
    {
        case ES:
            return EScount;
            break;
        case EG:
            return EGcount;
            break;
        case ET:
            return ETcount;
            break;
    }
}

int EarthArmy::getDeadUnitsCount(UnitType unitType) const
{
    switch (unitType)
    {
        case ES:
            return deadEScount;
            break;
        case EG:
            return deadEGcount;
            break;
        case ET:
            return deadETcount;
            break;
    }
}

void EarthArmy::printArmy() const
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