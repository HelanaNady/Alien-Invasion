#include "AlienMonster.h"
#include "../Game.h"

AlienMonster::AlienMonster(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AM, health, power, attackCapacity)
{}

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
    int soldiersCapacity = attackCapacity / 2;
    int tanksCapacity = attackCapacity - soldiersCapacity;

    // Get the lists of earth soldiers and tanks to attack
    LinkedQueue<Unit*> soldiersList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ES, soldiersCapacity);
    LinkedQueue<Unit*> tanksList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ET, tanksCapacity);

    // Check for a successful attack
    bool attackCheck = false;

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    // Loop through the tanks and soldiers lists
    while (soldiersList.dequeue(enemyUnit) || tanksList.dequeue(enemyUnit))
    {
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

        // Nullify the pointer to avoid duplication
        enemyUnit = nullptr;

        // If this line is reached, at least one unit was attacked
        attackCheck = true;
    }
    return attackCheck;
}