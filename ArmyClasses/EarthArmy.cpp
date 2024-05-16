#include <iostream>

#include "EarthArmy.h"
#include "../UnitClasses/Unit.h"
#include "../Game.h"

int EarthArmy::infectionThreshold = 0;

EarthArmy::EarthArmy(Game* gamePtr): Army(gamePtr), infectedSoldiersCount(0)
{}

void EarthArmy::setInfectionThreshold(int threshold)
{
    infectionThreshold = threshold;
}

void EarthArmy::addUnit(Unit* unit)
{
    UnitType unitType = unit->getUnitType();

    switch (unitType)
    {
        case UnitType::ES:
            soldiers.enqueue(unit);
            if (dynamic_cast<EarthSoldier*>(unit)->isInfected()) // If the soldier is infected, increment the infected count
                infectedSoldiersCount++;
            break;

        case UnitType::ET:
            tanks.push(unit);
            break;

        case UnitType::EG:
            gunneries.enqueue(unit, dynamic_cast<EarthGunnery*>(unit)->getPriority());
            break;

        case UnitType::EH:
            healers.push(unit);
            break;
    }
}

Unit* EarthArmy::removeUnit(UnitType unitType)
{
    Unit* unit = nullptr;

    switch (unitType)
    {
        case UnitType::ES:
            soldiers.dequeue(unit);
            if (unit && dynamic_cast<EarthSoldier*>(unit)->isInfected()) // If the soldier is infected, decrement the infected count
                infectedSoldiersCount--;
            break;

        case UnitType::ET:
            tanks.pop(unit);
            break;

        case UnitType::EG:
            int dummyPri;
            gunneries.dequeue(unit, dummyPri);
            break;

        case UnitType::EH:
            healers.pop(unit);
            break;
    }

    return unit;
}

Unit* EarthArmy::pickAttacker(UnitType unitType)
{
    Unit* unit = nullptr;
    int dummyPri = 0;

    switch (unitType)
    {
        case UnitType::ES:
            soldiers.peek(unit);
            break;

        case UnitType::EG:
            gunneries.peek(unit, dummyPri);
            break;

        case UnitType::ET:
            tanks.peek(unit);
            break;

        case UnitType::EH:
            healers.peek(unit);
            break;
    }

    return unit;
}

bool EarthArmy::attack()
{
    // Flag to check if the army attacked
    bool didArmyAttack = false;

    UnitType unitTypes[4] = { UnitType::ES, UnitType::EG, UnitType::ET, UnitType::EH };
    for (int i = 0; i < 4; i++)
    {
        // Pick an attacker from the army to attack
        Unit* attacker = pickAttacker(unitTypes[i]);

        if (attacker)
        {
            // Attack the enemy
            bool didUnitAttack = attacker->attack();

            // Healers need to be killed once they attack
            if (attacker->getUnitType() == UnitType::EH && didUnitAttack)
                killHealUnit();

            // Add the attacker to the current attackers queue
            if (didUnitAttack)
                currentAttackers.enqueue(attacker);

            // If any unit attacked, the army attacked
            didArmyAttack = didArmyAttack || didUnitAttack;
        }
    }

    return didArmyAttack; // Return whether the army attacked
}

bool EarthArmy::isDead() const
{
    return soldiers.getCount() + tanks.getCount() + gunneries.getCount() == 0;
}

bool EarthArmy::needAllyHelp() const
{
    return getInfectionPercentage() >= infectionThreshold;
}

void EarthArmy::printArmy() const
{
    std::cout << "Infected percentage = " << getInfectionPercentage() << "%" << std::endl;

    std::cout << std::endl << soldiers.getCount() << " ES [";
    soldiers.printList();
    std::cout << "]" << std::endl;

    std::cout << tanks.getCount() << " ET [";
    tanks.printList();
    std::cout << "]" << std::endl;

    std::cout << gunneries.getCount() << " EG [";
    gunneries.printList();
    std::cout << "]" << std::endl;

    std::cout << healers.getCount() << " EH [";
    healers.printList();
    std::cout << "]" << std::endl;
}

void EarthArmy::killHealUnit()
{
    Unit* healerUnit = nullptr;

    // Remove the healer from its list
    healers.pop(healerUnit);

    // Make unit health 0
    healerUnit->receiveDamage(healerUnit->getHealth());

    // Add healer unit to killed list
    gamePtr->addToKilledList(healerUnit);
}

void EarthArmy::spreadInfection()
{
    int soldiersCount = soldiers.getCount();
    int soldiersToInfect = infectedSoldiersCount;

    // if there are no soldiers to infect, return
    if (soldiersCount == 0)
        return;

    // Infect random soldiers
    for (int i = 0; i < soldiersToInfect; i++)
    {
        // Generate random number and decide to infect or not accordingly
        int x = rand() % 100 + 1;
        if (x > INFECTION_SPREAD_CHANCE)
            continue;

        // Get a random index to infect
        int randomIndex = rand() % soldiersCount;

        // Infect the soldier at the random index and re-enqueue the soldiers
        Unit* soldier = nullptr;
        for (int j = 0; j < soldiersCount; j++)
        {
            soldiers.dequeue(soldier);

            if (j == randomIndex)
            {
                if (dynamic_cast<EarthSoldier*>(soldier)->getInfection())
                    infectedSoldiersCount++;
            }

            soldiers.enqueue(soldier);
        }
    }
}

int EarthArmy::getUnitsCount(UnitType unitType) const
{
    switch (unitType)
    {
        case UnitType::ES:
            return soldiers.getCount();

        case UnitType::EG:
            return gunneries.getCount();

        case UnitType::ET:
            return tanks.getCount();

        case UnitType::EH:
            return healers.getCount();
    }

    return 0;
}

float EarthArmy::getInfectionPercentage() const
{
    if (soldiers.getCount() == 0)
        return 0;

    return (float) infectedSoldiersCount * 100 / soldiers.getCount();
}

int EarthArmy::getInfectedSoldiersCount() const
{
    return infectedSoldiersCount;
}

EarthArmy::~EarthArmy()
{
    // Delete all units in the army
    Unit* unit = nullptr;
    int dummyPri = 0;

    while (soldiers.dequeue(unit))
    {
        delete unit;
        unit = nullptr;
    }

    while (tanks.pop(unit))
    {
        delete unit;
        unit = nullptr;
    }

    while (gunneries.dequeue(unit, dummyPri))
    {
        delete unit;
        unit = nullptr;
    }

    while (healers.pop(unit))
    {
        delete unit;
        unit = nullptr;
    }
}