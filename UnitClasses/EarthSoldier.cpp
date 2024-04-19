#include "EarthSoldier.h"
#include "../Game.h"
#include "../Containers/LinkedQueue.h"

#include <iostream>

EarthSoldier::EarthSoldier(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::ES, health, power, attackCapacity)
{}

void EarthSoldier::print()
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "ES " << getId() << " shots [";
        foughtUnits.printList();
        std::cout << "]" << std::endl;

        clearFoughtUnits(); // Clear the list after printing
    }
}

void EarthSoldier::attack()
{
    LinkedQueue<Unit*> enemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AS, attackCapacity);
    LinkedQueue<Unit*> tempList;
    Unit* enemyUnit = nullptr;

    while (!enemyList.isEmpty())
    {
        enemyList.dequeue(enemyUnit);
        // Check if it were attacked before or not
        if (enemyUnit->isFirstAttack())
            enemyUnit->setFirstTimeAttack(gamePtr->getCurrentTimestep());

        // Receive damage and check whether it's dead or not
        enemyUnit->receiveDamage(calcUAP(enemyUnit));
        if (enemyUnit->isDead())
            gamePtr->addToKilledList(enemyUnit);
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
