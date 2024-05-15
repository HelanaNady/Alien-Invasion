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
        gamePtr->log("Earth " + getUnitTypeString() + " " + toString() + " is healing " + unitToHeal->getUnitTypeString() + " " + unitToHeal->toString() + " with UHP " + std::to_string(calcUAP(unitToHeal)));// Check if unit has spent more than 10  consecutive time steps in UML
        if (unitToHeal->hasWaitedForTooLong())
        {
            unitToHeal->receiveDamage(unitToHeal->getHealth()); // Make unit health 0 
            gamePtr->addToKilledList(unitToHeal); // Add unit to killed list

            gamePtr->log("Earth " + unitToHeal->getUnitTypeString() + " " + unitToHeal->toString() + " has been killed because it spent more than 10 time steps in UML");

            continue;
        }

        // Heal each unit with the appropriate heal power
        unitToHeal->receiveHeal(calcUAP(unitToHeal));

        // Add the unit back to its list if completely healed, otherwise re-add to the UML
        if (unitToHeal->isHealed())
        {
            EarthSoldier* infectedSoldier = dynamic_cast<EarthSoldier*>(unitToHeal); // If the unit was an infected, additional heal is needed
            if (infectedSoldier && infectedSoldier->isInfected())
                healInfection(infectedSoldier);

            gamePtr->addUnit(unitToHeal); // Add it to its list whether it was infected or not
        }
        else
            gamePtr->addUnitToMaintenanceList(unitToHeal);

        gamePtr->log("Earth " + unitToHeal->getUnitTypeString() + " " + unitToHeal->toString() + " has healed Earth " + unitToHeal->getUnitTypeString() + " " + unitToHeal->toString());

        // Store the IDs of the units that recieved heal to be printed later
        foughtUnits.enqueue(unitToHeal->getId());

        // Nullify the pointer to avoid duplication
        unitToHeal = nullptr;

        // If this line was reached, at least one heal was successful
        healCheck = true;
    }

    return healCheck;
}

void HealUnit::healInfection(EarthSoldier* recoveredSoldier)
{
    recoveredSoldier->loseInfection(); // Turn the infection flag off
    recoveredSoldier->gainImmunity(); // Make it immune to furure infections
}