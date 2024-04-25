#include <iostream>

#include "AlienArmy.h"
#include "../UnitClasses/Unit.h"

AlienArmy::AlienArmy(Game* gamePtr): Army(gamePtr), dronesToggler(false)
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
        case UnitType::AS:
            return soldiers.getCount();
        case UnitType::AM:
            return monsters.getCount();
        case UnitType::AD:
            return drones.getCount();
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

bool AlienArmy::attack()
{
    bool didArmyAttack = false; // Flag to check if the army attacked

    UnitType unitTypes[4] = { AS, AM, AD, AD };
    for (int i = 0; i < 4; i++)
    {
        Unit* attacker = pickAttacker(unitTypes[i]);

        if (attacker)
        {
            // If only one drone exists or less, don't attack
            if (drones.getCount() < 1 && i == 2)
                break;

            currentAttackers.enqueue(attacker);
            bool didUnitAttack = attacker->attack(); // Attack the enemy
            didArmyAttack = didArmyAttack || didUnitAttack; // If any unit attacked, the army attacked
        }
    }

    return didArmyAttack; // Return whether the army attacked
}

bool AlienArmy::isDead() const
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