#include "HealUnit.h"
#include "../Game.h"

HealUnit::HealUnit(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EH, health, power, attackCapacity)
{}

void HealUnit::printFought()
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "EH " << getId() << " heals [";
        foughtUnits.printList();
        std::cout << "]" << std::endl;

        clearFoughtUnits(); // Clear the list after printing
    }
}

bool HealUnit::attack()
{
    LinkedQueue<HealableUnit*> unitsToHeal = gamePtr->getUnitsToMaintainList(attackCapacity);

    // Create a pointer to the unit to heal
    HealableUnit* unitToHeal = nullptr;

    // Check if any heal happened
    bool healCheck = false;

    while (unitsToHeal.dequeue(unitToHeal))
    {
        // Check if unit has spent more than 10  consecutive time steps in UML
        if (unitToHeal->hasWaitedForTooLong())
        {
            unitToHeal->receiveDamage(unitToHeal->getHealth()); // Make unit health 0 
            gamePtr->addToKilledList(unitToHeal); // Add unit to killed list

            continue;
        }

        // Heal the unit
        unitToHeal->receiveHeal(calcUAP(unitToHeal));

        // If unit's health is more than 20% of its initial health, make it join battle
        if (unitToHeal->isHealed())
            gamePtr->addUnit(unitToHeal);
        else
            gamePtr->addUnitToMaintenanceList(unitToHeal);

        // Store the IDs of the healed units to be printed later
        foughtUnits.enqueue(unitToHeal->getId());

        // Nullify the pointer to avoid duplication
        unitToHeal = nullptr;

        // If this line was reached, at least one heal was successful
        healCheck = true;
    }

    return healCheck;
}
