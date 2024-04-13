#include "EarthTank.h"
#include "../Game.h"
#include "../Containers/LinkedQueue.h"

#include <cmath>

EarthTank::EarthTank(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::ET, health, power, attackCapacity)
{}

void EarthTank::print() const
{
    std::cout << "ET " << this->getId() << " shots [";
    foughtUnits.printList();
    std::cout << "]\n";
}

void EarthTank::attack()
{
    LinkedQueue<Unit*> monsterEnemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AM, attackCapacity);
    LinkedQueue<Unit*> soldierEnemyList;
    LinkedQueue<Unit*> tempList;
    Unit* enemyUnit = nullptr;

    // Calculating the number of alien soldiers that needs to be killed
    int soldiersToKill = std::ceil(gamePtr->getUnitsCount(ALIEN, AS) - (gamePtr->getUnitsCount(EARTH, AS) / 0.8));
    int deadSoldiers = 0; 

    for (int i = 0; i < attackCapacity; i++)
    {
        /* Re-adding the fought alive soldiers to their list to be foughht again
            till the required number of kills is reached */
        if (soldierEnemyList.isEmpty() && deadSoldiers < soldiersToKill) 
        {
            Unit* tempUnitPtr = nullptr; 
            while (tempList.dequeue(tempUnitPtr)) 
                gamePtr->addUnit(tempUnitPtr); 
        }


        if (deadSoldiers < soldiersToKill)
        {
            soldierEnemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AS, attackCapacity); 
            soldierEnemyList.dequeue(enemyUnit);
        }
        else
            monsterEnemyList.dequeue(enemyUnit);


        if (!enemyUnit)
            continue;

        // Check if it were attacked before or not 
        if (enemyUnit->getTattack() == -1) 
        {
            enemyUnit->setTattack(gamePtr->getCurrentTimestep()); 
        }

        // Recieve damage and check whether it's dead or not
        enemyUnit->recieveDamage(this->calcUAP(enemyUnit)); 
        if (enemyUnit->getHealth() == 0)
        {
            gamePtr->killUnit(enemyUnit);
            enemyUnit->setTdestruction(gamePtr->getCurrentTimestep());
            if(deadSoldiers < soldiersToKill)
            deadSoldiers++;
        }
        else
            tempList.enqueue(enemyUnit);
    }


    // Re-adding attacked units to their original lists
    Unit* tempUnitPtr = nullptr;
    while (tempList.dequeue(tempUnitPtr))
        gamePtr->addUnit(tempUnitPtr);

}
