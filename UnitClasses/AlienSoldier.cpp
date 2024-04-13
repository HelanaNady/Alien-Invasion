#include "AlienSoldier.h"
#include "../Game.h"

AlienSoldier::AlienSoldier(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AS, health, power, attackCapacity)
{}

void AlienSoldier::print() const
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "AS " << getId() << " shots [";
        foughtUnits.printList();
        std::cout << "]\n";
    }
}

void AlienSoldier::attack()
{
    // Get the lists of earth soldiers to attack
    LinkedQueue<Unit*> soldiersList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ES, attackCapacity);

    // Create a temporary list to store the alive units
    LinkedQueue<Unit*> tempList;

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    while (!soldiersList.isEmpty())
    {
        // Get the unit and remove it from the list
        soldiersList.dequeue(enemyUnit);

        // Set the first attack time if it's the first time attacking
        if (enemyUnit->isFirstAttack())
            enemyUnit->setFirstTimeAttack(gamePtr->getCurrentTimestep());

        // Calculate the UAP and apply the damage
        enemyUnit->receiveDamage(calcUAP(enemyUnit));

        // If the unit is dead, added to killedList, otherwise add it to the tempList
        if (enemyUnit->isDead())
            gamePtr->killUnit(enemyUnit);
        else
            tempList.enqueue(enemyUnit);

        // Store the IDs of the fought units to be printed later
        foughtUnits.enqueue(enemyUnit->getId());
    }

    // Empty the tempList and re-add the alive units back to their lists
    Unit* unit = nullptr;
    while (tempList.dequeue(unit))
        gamePtr->addUnit(unit);
}