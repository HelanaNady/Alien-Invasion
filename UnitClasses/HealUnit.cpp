#include "HealUnit.h"
#include "../Game.h"

HealUnit::HealUnit(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EH, health, power, attackCapacity)
{}

void HealUnit::printUnit()
{
    std::cout << "HU " << id;
}

bool HealUnit::attack()
{
    // Get the list of units to heal
    LinkedQueue<HealableUnit*> unitsToHeal = gamePtr->getUnitsToMaintainList(attackCapacity);

    std::string healedUnits = "";

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

        // Heal each unit with the appropriate heal power
        // Inside receiveHeal, if unit is infected, it would apply only half of UAP so it would take as twice as long to heal
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
            gamePtr->addUnitToMaintenanceList(unitToHeal); // Add it back to the UML if not completely healed

        // Store the IDs of the units that received heal to be printed later
        if (healedUnits != "")
            healedUnits += ", ";
        healedUnits += std::to_string(unitToHeal->getId());

        // Nullify the pointer
        unitToHeal = nullptr;

        // If this line was reached, at least one heal was successful
        healCheck = true;
    }

    if (healedUnits != "")
        gamePtr->registerAttack(this, "heals", healedUnits);

    return healCheck;
}

void HealUnit::healInfection(EarthSoldier* recoveredSoldier)
{
    recoveredSoldier->loseInfection(); // Turn the infection flag off
    recoveredSoldier->gainImmunity(); // Make it immune to future infections
}