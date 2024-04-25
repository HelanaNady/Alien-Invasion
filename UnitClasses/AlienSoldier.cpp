#include "AlienSoldier.h"
#include "../Game.h"

AlienSoldier::AlienSoldier(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AS, health, power, attackCapacity)
{}

void AlienSoldier::printFought()
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "AS " << getId() << " shots [";
        foughtUnits.printList();
        std::cout << "]" << std::endl;

        clearFoughtUnits(); // Clear the list after printing
    }
}

void AlienSoldier::attack()
{
    // Get the lists of earth soldiers to attack
    LinkedQueue<Unit*> soldiersList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ES, attackCapacity);

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    while (soldiersList.dequeue(enemyUnit))
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