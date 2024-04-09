#include <iostream>

#include "AlienArmy.h"
#include "../UnitClasses/Unit.h"

AlienArmy::AlienArmy(): AScount(0), AMcount(0), ADcount(0), deadAScount(0), deadAMcount(0), deadADcount(0), dronesToggler(false)
{}

void AlienArmy::addUnit(Unit* unit)
{
    UnitType unitType = unit->getUnitType();

    switch (unitType)
    {
        case UnitType::AS:
            soldiers.enqueue(unit);
            AScount++;
            break;


        case UnitType::AM:
            monsters.insert(unit);
            AMcount++;
            break;

        case UnitType::AD:
            if (dronesToggler)
                drones.enqueue(unit);
            else
                drones.enqueueFront(unit);
            dronesToggler = !dronesToggler;
            ADcount++;
            break;
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

int AlienArmy::getUnitsCount(UnitType unitType) const
{
    switch (unitType)
    {
        case AS:
            return AScount;
            break;
        case AM:
            return AMcount;
            break;
        case AD:
            return ADcount;
            break;
    }

}

int AlienArmy::getDeadUnitsCount(UnitType unitType) const
{
    switch (unitType)
    {
        case AS:
            return deadAScount;
            break;
        case AM:
            return deadAMcount;
            break;
        case AD:
            return deadADcount;
            break;
    }
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

AlienArmy::~AlienArmy()
{
    // Delete all units in the army
    Unit* unit = nullptr;
    while (!soldiers.isEmpty())
    {
        soldiers.dequeue(unit);
        delete unit;
    }

    while (!monsters.isEmpty())
    {
        monsters.remove(0, unit);
        delete unit;
    }

    while (!drones.isEmpty())
    {
        drones.dequeue(unit);
        delete unit;
    }
}