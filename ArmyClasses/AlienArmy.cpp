#include <iostream>

#include "AlienArmy.h"
#include "../UnitClasses/Unit.h"

AlienArmy::AlienArmy(): soldiersCount(0), monstersCount(0), dronesCount(0), dronesToggler(false)
{}

void AlienArmy::addUnit(Unit* unit)
{
    UnitType unitType = unit->getUnitType();

    switch (unitType)
    {
        case UnitType::AS:
        {
            soldiers.enqueue(unit);
            soldiersCount++;
            break;
        }

        case UnitType::AM:
        {
            monsters.insert(unit);
            monstersCount++;
            break;
        }

        case UnitType::AD:
        {
            if (dronesToggler)
                drones.enqueue(unit);
            else
                drones.enqueueFront(unit);

            dronesToggler = !dronesToggler;
            dronesCount++;
            break;
        }
    }
}

Unit* AlienArmy::removeUnit(UnitType unitType)
{
    Unit* unit = nullptr;

    switch (unitType)
    {
        case UnitType::AS:
            soldiers.dequeue(unit);
            break;

        case UnitType::AM:
            if (!monsters.isEmpty())
                monsters.remove((rand() % monsters.getCount()), unit);
            break;

        case UnitType::AD:
            if (dronesToggler)
                drones.dequeue(unit);
            else
                drones.dequeueBack(unit);

            dronesToggler = !dronesToggler;
            break;
    }

    return unit;
}

void AlienArmy::printArmy() const
{
    std::cout << "============== Alien Army Alive Units ==============" << std::endl;

    std::cout << soldiers.getCount() << " AS [";
    soldiers.printList();
    std::cout << "]" << std::endl;

    std::cout << monsters.getCount() << " AM [";
    monsters.printList();
    std::cout << "]" << std::endl;

    std::cout << drones.getCount() << " AD [";
    drones.printList();
    std::cout << "]" << std::endl;
}

void AlienArmy::attack()
{}