#include "AlienMonster.h"
#include "../Game.h"

int AlienMonster::infectingProbability = 0;

AlienMonster::AlienMonster(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AM, health, power, attackCapacity)
{}

void AlienMonster::setInfectingProbability(int probability)
{
    infectingProbability = probability;
}

void AlienMonster::printFought()
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "AM " << getId() << " shots [";
        foughtUnits.printList();
        std::cout << "]" << std::endl;

        clearFoughtUnits(); // Clear the list after printing
    }
}

bool AlienMonster::attack()
{
    // Calculate the number of soldiers and tanks to attack
    int soldiersCapacity = attackCapacity / 3;
    int tanksCapacity = attackCapacity / 3;
    int saversCapacity = attackCapacity - soldiersCapacity - tanksCapacity;

    // Get the lists of earth soldiers and tanks to attack
    LinkedQueue<Unit*> soldiersList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ES, soldiersCapacity);
    LinkedQueue<Unit*> tanksList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ET, tanksCapacity);
    LinkedQueue<Unit*> saversList = gamePtr->getEnemyList(ArmyType::EARTH_ALLIED, UnitType::SU, saversCapacity);

    // Check for a successful attack
    bool attackCheck = false;

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    // Loop through the tanks and soldiers lists
    while (soldiersList.dequeue(enemyUnit) || tanksList.dequeue(enemyUnit) || saversList.dequeue(enemyUnit))
    {
        // Check if the enemy unit is an Earth Soldier and infect it if the probability is met
        int x = rand() % 100 + 1;
        if (enemyUnit->getUnitType() == UnitType::ES && x <= infectingProbability)
        {
            gamePtr->log("Alien " + getUnitTypeString() + " " + toString() + " is infecting Earth Soldier " + enemyUnit->toString());
            dynamic_cast<EarthSoldier*>(enemyUnit)->getInfection();
            gamePtr->addUnit(enemyUnit);
            gamePtr->log("Alien " + getUnitTypeString() + " " + toString() + " infected Earth Soldier " + enemyUnit->toString());
            continue;
        }

        gamePtr->log("Alien " + getUnitTypeString() + " " + toString() + " is attacking Earth " + enemyUnit->getUnitTypeString() + " " + enemyUnit->toString() + " with UAP " + std::to_string(calcUAP(enemyUnit)));

        // Calculate the UAP and apply the damage
        enemyUnit->receiveDamage(calcUAP(enemyUnit));

        // Check if the unit is dead, needs healing or can join the battle
        if (enemyUnit->isDead())
            gamePtr->addToKilledList(enemyUnit);
        else if (enemyUnit->needsHeal())
            gamePtr->addUnitToMaintenanceList(dynamic_cast<HealableUnit*>(enemyUnit));
        else
            gamePtr->addUnit(enemyUnit);

        // Store the IDs of the fought units to be printed later
        foughtUnits.enqueue(enemyUnit->getId());

        gamePtr->log("Alien " + getUnitTypeString() + " " + toString() + " attacked Earth " + enemyUnit->getUnitTypeString() + " " + enemyUnit->toString());

        attackCheck = true;

        // Nullify the pointer to avoid duplication
        enemyUnit = nullptr;
    }

    return attackCheck;
}