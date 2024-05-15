#include <iostream>

#include "AlienArmy.h"
#include "../UnitClasses/Unit.h"

AlienArmy::AlienArmy(Game* gamePtr): Army(gamePtr),
dronesAddingToggler(false), dronesRemovingToggler(false), dronesPickingToggler(false)
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
            if (dronesAddingToggler)
                drones.enqueue(unit);
            else
                drones.enqueueFront(unit);

            dronesAddingToggler = !dronesAddingToggler;
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
            if (dronesRemovingToggler)
                drones.dequeue(unit);
            else
                drones.dequeueBack(unit);

            dronesRemovingToggler = !dronesRemovingToggler;
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
                monsters.entryAt(unit, (rand() % monsters.getCount())); // Pick a random monster
            break;

        case UnitType::AD:
            if (dronesPickingToggler) // To pick the drones in a once front, once back order
                drones.peek(unit);
            else
                drones.peekBack(unit);

            dronesPickingToggler = !dronesPickingToggler;
            break;
    }

    return unit;
}

bool AlienArmy::attack()
{
    // Flag to check if the army attacked
    bool didArmyAttack = false;

    UnitType unitTypes[4] = { UnitType::AS, UnitType::AM, UnitType::AD, UnitType::AD };
    for (int i = 0; i < 4; i++)
    {
        // Pick an attacker from the army to attack
        Unit* attacker = pickAttacker(unitTypes[i]);

        if (attacker)
        {
            // If drone is attacking and there are less than 2 drones, skip the attack
            if (unitTypes[i] == UnitType::AD && drones.getCount() < 2)
                continue;

            // Attack the enemy
            bool didUnitAttack = attacker->attack();

            // Add the attacker to the current attackers queue
            if (didUnitAttack)
                currentAttackers.enqueue(attacker);

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