#include "HealUnit.h"
#include "../Game.h"

HealUnit::HealUnit(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EH, health, power, attackCapacity)
{}

void HealUnit::attack()
{
    LinkedQueue<Unit*> unitsToHeal = gamePtr->getUnitsToMaintainList(attackCapacity);

    // Create a pointer to the unit to heal
    Unit* unitToHeal = nullptr;

    while (unitsToHeal.dequeue(unitToHeal))
    {
        gamePtr->log("Earth " + getUnitTypeString() + " " + toString() + " is healing " + unitToHeal->getUnitTypeString() + " " + unitToHeal->toString() + " with UHP " + std::to_string(calcUAP(unitToHeal)));
        // Check if unit has spend more than 10 time steps in UML
        if (gamePtr->getCurrentTimestep() - unitToHeal->getUMLjoinTime() > 10)
        {
            unitToHeal->receiveDamage(unitToHeal->getHealth()); // Make unit health 0
            gamePtr->addToKilledList(unitToHeal); // Add unit to killed list

            gamePtr->log("Earth " + unitToHeal->getUnitTypeString() + " " + unitToHeal->toString() + " has been killed because it spent more than 10 time steps in UML");

            continue;
        }

        // Heal the unit
        unitToHeal->receiveHeal(calcUAP(unitToHeal));

        gamePtr->log("Earth " + unitToHeal->getUnitTypeString() + " " + unitToHeal->toString() + " has been healed to " + std::to_string(unitToHeal->getHealth()) + " health");

        // If unit's health is more than 20% of its initial health, make it join battle
        if (unitToHeal->getHealth() > unitToHeal->getInitialHealth() * 0.2)
            gamePtr->addUnit(unitToHeal);
        else
            gamePtr->addUnitToMaintenanceList(unitToHeal);

        gamePtr->log("Earth " + unitToHeal->getUnitTypeString() + " " + unitToHeal->toString() + " has healed Earth " + unitToHeal->getUnitTypeString() + " " + unitToHeal->toString());

        // Nullify the pointer to avoid duplication
        unitToHeal = nullptr;

    }
}
