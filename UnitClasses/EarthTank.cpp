#include <cmath>

#include "EarthTank.h"
#include "../Game.h"
#include "../Containers/LinkedQueue.h"

EarthTank::EarthTank(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::ET, health, power, attackCapacity)
{}

void EarthTank::printFought()
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "ET " << getId() << " shots [";
        foughtUnits.printList();
        std::cout << "]" << std::endl;

        clearFoughtUnits(); // Clear the list after printing
    }
}

void EarthTank::attack()
{
    LinkedQueue<Unit*> monsterEnemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AM, attackCapacity);
    LinkedQueue<Unit*> soldierEnemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AS, attackCapacity);
    LinkedQueue<Unit*> tempList;

    // Calculating the number of alien soldiers that needs to be killed
    int soldiersToKill = std::ceil(gamePtr->getUnitsCount(ALIEN, AS) - (gamePtr->getUnitsCount(EARTH, AS) / 0.8));
    int deadSoldiers = 0;

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    for (int i = 0; i < attackCapacity; i++)
    {
        /* Re-adding the fought alive soldiers to their list to be fought again
            till the required number of kills is reached */
        if (soldierEnemyList.isEmpty() && deadSoldiers < soldiersToKill)
        {
            Unit* tempUnitPtr = nullptr;
            while (tempList.dequeue(tempUnitPtr))
                gamePtr->addUnit(tempUnitPtr);
            soldierEnemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AS, attackCapacity);
        }

        if (deadSoldiers < soldiersToKill)
            soldierEnemyList.dequeue(enemyUnit);
        else
            monsterEnemyList.dequeue(enemyUnit);

        // If no unit was received and at least one of the lists weren't empty, don't increment the counter
        if (!enemyUnit)
            continue;

        // Check if it were attacked before or not 
        if (enemyUnit->isFirstAttack())
            enemyUnit->setFirstTimeAttack(gamePtr->getCurrentTimestep());

        // Calculate the UAP and apply the damage
        enemyUnit->receiveDamage(calcUAP(enemyUnit));

        // Check if the unit is dead or can join the battle
        if (enemyUnit->isDead())
        {
            gamePtr->addToKilledList(enemyUnit);
            if (deadSoldiers < soldiersToKill)
                deadSoldiers++;
        }
        else
            tempList.enqueue(enemyUnit);

        // Nullify the pointer to avoid duplication
        enemyUnit = nullptr;
    }

    // Re-adding attacked units to their original lists
    Unit* tempUnitPtr = nullptr;
    while (tempList.dequeue(tempUnitPtr))
        gamePtr->addUnit(tempUnitPtr);
}

int EarthTank::getHealPriority() const
{
    return health;
}