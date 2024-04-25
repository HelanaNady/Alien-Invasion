#include "HealUnit.h"
#include "../Game.h"

HealUnit::HealUnit(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EH, health, power, attackCapacity)
{}

void HealUnit::attack()
{
    LinkedQueue<Unit*> unitsToHeal = gamePtr->getUnitsToMaintainList(attackCapacity);

    Unit* unitToHeal = nullptr;
    while (unitsToHeal.dequeue(unitToHeal))
    {
        // Check if unit has spend more than 10 time steps in UML
        if (gamePtr->getCurrentTimestep() - unitToHeal->getUMLjoinTime() > 10)
        {
            unitToHeal->receiveDamage(unitToHeal->getHealth()); // Make unit health 0
            gamePtr->addToKilledList(unitToHeal);
        }

        // Heal the unit
        unitToHeal->receiveHeal(calcUAP(unitToHeal));

        if (unitToHeal->getHealth() > unitToHeal->getInitialHealth() * 0.2)
            gamePtr->addUnit(unitToHeal);
        else
            gamePtr->addUnitToMaintenanceList(unitToHeal);
    }
}
