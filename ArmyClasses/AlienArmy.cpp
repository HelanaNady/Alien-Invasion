#include <iostream>

#include "AlienArmy.h"
#include "../UnitClasses/Unit.h"

AlienArmy::AlienArmy(): dronesToggler(false)
{}

void AlienArmy::addUnit(Unit* unit)
{
    UnitType unitType = unit->getUnitType();

    switch (unitType)
    {
        case UnitType::AS:
            soldiers.enqueue(unit);
            break;

        case UnitType::AM:
            monsters.insert(unit);
            break;

        case UnitType::AD:
            if (dronesToggler)
                drones.enqueue(unit);
            else
                drones.enqueueFront(unit);

            dronesToggler = !dronesToggler;
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
                monsters.entryAt(unit, (rand() % monsters.getCount()));
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

Unit* AlienArmy::pickAttacker(UnitType unitType)
{
    Unit* unit = nullptr;

    switch (unitType)
    {
        case UnitType::AS:
            soldiers.peek(unit);
            break;

        case UnitType::AM:
            if (!monsters.isEmpty())
                monsters.entryAt(unit, (rand() % monsters.getCount()));
            break;

        case UnitType::AD:
            if (dronesToggler)
                drones.peek(unit);
            else
                drones.peekBack(unit);

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
            return soldiers.getCount();
            break;
        case AM:
            return monsters.getCount();
            break;
        default:
            return drones.getCount();
            break;
    }

    return 0;
}

void AlienArmy::printArmy() const
{
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
{
    Unit* attacker = pickAttacker(UnitType::AS);
    if (attacker)
    {
        attacker->attack();
        currentAttackers.enqueue(attacker);
    }

    attacker = pickAttacker(UnitType::AM);
    if (attacker)
    {
        attacker->attack();
        currentAttackers.enqueue(attacker);
    }

    if (drones.getCount() > 1)
    {
        attacker = pickAttacker(UnitType::AD);
        attacker->attack();
        currentAttackers.enqueue(attacker);

        attacker = pickAttacker(UnitType::AD);
        attacker->attack();
        currentAttackers.enqueue(attacker);
    }
}

bool AlienArmy::isDead()
{
    return soldiers.getCount() + monsters.getCount() + drones.getCount() == 0;
}

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