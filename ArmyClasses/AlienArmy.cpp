#include <iostream>

#include "AlienArmy.h"
#include "../UnitClasses/Unit.h"
#include "../Game.h"

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

    gamePtr->log("Removing a unit from the Alien Army of type " + Unit::unitTypeString(unitType) + "...");

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
                monsters.entryAt(unit, (rand() % monsters.getCount()));
            break;

        case UnitType::AD:
            if (dronesPickingToggler)
                drones.peek(unit);
            else
                drones.peekBack(unit);

            dronesPickingToggler = !dronesPickingToggler;
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
            switch (unitTypes[i])
            {
                case UnitType::AS:
                    gamePtr->log("Attacking with Alien Soldier: " + attacker->toString());
                    break;

                case UnitType::AM:
                    gamePtr->log("Attacking with Alien Monster: " + attacker->toString());
                    break;

                case UnitType::AD:
                    if (i == 3)
                        gamePtr->log("Attacking with the first Alien Drone: " + attacker->toString());
                    else
                        gamePtr->log("Attacking with the second Alien Drone: " + attacker->toString());
                    break;

            }

            // If drone is attacking and there are less than 2 drones, skip the attack
            if (unitTypes[i] == UnitType::AD && drones.getCount() < 2)
            {
                gamePtr->log("Not enough Alien Drones to attack. We have " + std::to_string(drones.getCount()));
                continue;
            }

            // Attack the enemy
            bool didUnitAttack = attacker->attack();

            // Add the attacker to the current attackers queue
            if (didUnitAttack)
                currentAttackers.enqueue(attacker);
        }
        else
        {
            switch (unitTypes[i])
            {
                case UnitType::AS:
                    gamePtr->log("No Alien Soldier to attack with");
                    break;

                case UnitType::AM:
                    gamePtr->log("No Alien Monster to attack with");
                    break;

                case UnitType::AD:
                    gamePtr->log("No Alien Drone to attack with");
                    break;
            }
        }
    }

    return didArmyAttack;
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