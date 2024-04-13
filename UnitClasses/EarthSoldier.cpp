#include "EarthSoldier.h"
#include "../Game.h"
#include "../Containers/LinkedQueue.h"

#include <iostream>

EarthSoldier::EarthSoldier(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::ES, health, power, attackCapacity)
{
}

void EarthSoldier::print() const
{
    std::cout << "ES " << this->getId() << " shots [";
    foughtUnits.printList();
    std::cout << "]\n";
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
        if (enemyUnit->getFirstAttackTime() == -1)
        {
            enemyUnit->setFirstTimeAttack(gamePtr->getCurrentTimestep());
        }

        // Recieve damage and check whether it's dead or not
        enemyUnit->recieveDamage(this->calcUAP(enemyUnit));
        if (enemyUnit->getHealth() == 0)
        {
            gamePtr->killUnit(enemyUnit);
            enemyUnit->setDestructionTime(gamePtr->getCurrentTimestep());
        }
        else
            tempList.enqueue(enemyUnit);

        // Store the IDs of the fought units to be printed later
        foughtUnits.enqueue(enemyUnit->getId());
    }


    // Empty the tempList and re-add the alive units back to their lists
    while (!tempList.isEmpty())
    {
        Unit* tempUnitPtr = nullptr;
        tempList.dequeue(tempUnitPtr);
        gamePtr->addUnit(tempUnitPtr);
    }
}
