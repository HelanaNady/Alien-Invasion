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

        // Infected units take twice as long to get healed
        if(unitToHeal->getUnitType() == UnitType::ES)
        dynamic_cast<EarthSoldier*>(unitToHeal)->isInfected() ? slowHeal(unitToHeal) : normalHeal(unitToHeal);  

        // Store the IDs of the units that recieved heal to be printed later
        foughtUnits.enqueue(unitToHeal->getId());

        // Nullify the pointer to avoid duplication
        unitToHeal = nullptr;

        // If this line was reached, at least one heal was successful
        healCheck = true;
    }

    return healCheck;
}

void HealUnit::normalHeal(HealableUnit* unitToHeal)
{
    unitToHeal->receiveHeal(calcUAP(unitToHeal));

    if (unitToHeal->isHealed())
        gamePtr->addUnit(unitToHeal);
    else
        gamePtr->addUnitToMaintenanceList(unitToHeal);
}

void HealUnit::slowHeal(HealableUnit* unitToHeal)
{
    EarthSoldier* soldierToHeal = dynamic_cast<EarthSoldier*>(unitToHeal);

    // Infected units take twice as long to get healed
    soldierToHeal->receiveHeal(calcUAP(unitToHeal) / 2);

    if (soldierToHeal->isHealed())
    {
        soldierToHeal->loseInfection();
        soldierToHeal->gainImmunity();
        gamePtr->addUnit(unitToHeal);
    }
    else
        gamePtr->addUnitToMaintenanceList(unitToHeal);
}
