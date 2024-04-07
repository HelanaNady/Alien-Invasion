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
    {
        EarthGunnery* temp = dynamic_cast<EarthGunnery*>(unit);
        gunneries.enqueue(temp, temp->getPriority());
    }
}

Unit* EarthArmy::removeUnit(UnitType unitType)
{
    Unit* unit = nullptr;

    if (unitType == UnitType::ES)
    {
        EarthSoldier* temp = nullptr;
        soldiers.dequeue(temp);
        unit = temp;
    }
    else if (unitType == UnitType::ET)
    {
        EarthTank* temp = nullptr;
        tanks.pop(temp);
        unit = temp;
    }
    else if (unitType == UnitType::EG)
    {
        int dummyPri;
        EarthGunnery* temp = nullptr;
        gunneries.dequeue(temp, dummyPri);
        unit = temp;
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