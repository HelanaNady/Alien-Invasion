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
            // If drone is attacking and there are less than 2 drones, skip the attack
            if (unitTypes[i] == UnitType::AD && drones.getCount() < 2)
                continue;

            // Add the attacker to the current attackers queue
            currentAttackers.enqueue(attacker);

            // Attack the enemy
            bool didUnitAttack = attacker->attack();

            // If any unit attacked, the army attacked
            didArmyAttack = didArmyAttack || didUnitAttack;
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
    while (soldiers.dequeue(unit))
    {
        delete unit;
        unit = nullptr;
    }

    while (monsters.remove(0, unit))
    {
        delete unit;
        unit = nullptr;
    }

    while (drones.dequeue(unit))
    {
        delete unit;
        unit = nullptr;
    }
}