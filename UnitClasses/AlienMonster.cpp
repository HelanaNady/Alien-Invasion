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

void AlienMonster::attack()
{
    // Calculate the number of soldiers and tanks to attack
    int soldiersCapacity = attackCapacity / 2;
    int tanksCapacity = attackCapacity - soldiersCapacity;

    // Get the lists of earth soldiers and tanks to attack
    LinkedQueue<Unit*> soldiersList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ES, soldiersCapacity);
    LinkedQueue<Unit*> tanksList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ET, tanksCapacity);

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    // Loop through the tanks and soldiers lists
    for (int i = 0; i < 2; i++)
    {
        LinkedQueue<Unit*>& currentList = (i == 0) ? soldiersList : tanksList; // Get the current list

        while (currentList.dequeue(enemyUnit))
        {
            gamePtr->log("Alien " + getUnitTypeString() + " " + toString() + " is attacking Earth " + enemyUnit->getUnitTypeString() + " " + enemyUnit->toString() + " with UAP " + std::to_string(calcUAP(enemyUnit)));

            // Set the first attack time if it's the first time attacking
            if (enemyUnit->isFirstAttack())
                enemyUnit->setFirstTimeAttack(gamePtr->getCurrentTimestep());

            // Calculate the UAP and apply the damage
            enemyUnit->receiveDamage(calcUAP(enemyUnit));

            // Check if the unit is dead, needs healing or can join the battle
            if (enemyUnit->isDead())
                gamePtr->addToKilledList(enemyUnit);
            else if (enemyUnit->needsHeal())
                gamePtr->addUnitToMaintenanceList(enemyUnit);
            else
                gamePtr->addUnit(enemyUnit);

            // Store the IDs of the fought units to be printed later
            foughtUnits.enqueue(enemyUnit->getId());

            gamePtr->log("Alien " + getUnitTypeString() + " " + toString() + " attacked Earth " + enemyUnit->getUnitTypeString() + " " + enemyUnit->toString());

            // Nullify the pointer to avoid duplication
            enemyUnit = nullptr;

        }
    }
}