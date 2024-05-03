#include "HealUnit.h"
#include "../Game.h"

HealUnit::HealUnit(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EH, health, power, attackCapacity)
{}

bool HealUnit::attack()
{
    LinkedQueue<Unit*> unitsToHeal = gamePtr->getUnitsToMaintainList(attackCapacity);

    // Create a pointer to the unit to heal
    Unit* unitToHeal = nullptr;

    while (unitsToHeal.dequeue(unitToHeal))
    {
        // Check if unit has spend more than 10 time steps in UML
        if (gamePtr->getCurrentTimestep() - unitToHeal->getUMLjoinTime() > 10)
        {
            unitToHeal->receiveDamage(unitToHeal->getHealth()); // Make unit health 0
            gamePtr->addToKilledList(unitToHeal); // Add unit to killed list

            continue;
        }

        // Heal the unit
        unitToHeal->receiveHeal(calcUAP(unitToHeal));

        // If unit's health is more than 20% of its initial health, make it join battle
        if (unitToHeal->getHealth() > unitToHeal->getInitialHealth() * 0.2)
            gamePtr->addUnit(unitToHeal);
        else
            gamePtr->addUnitToMaintenanceList(unitToHeal);

        // Nullify the pointer to avoid duplication
        unitToHeal = nullptr;
    }

    return true;
}
