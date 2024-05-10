#include <cmath>

#include "EarthTank.h"
#include "../Game.h"
#include "../Containers/LinkedQueue.h"

EarthTank::EarthTank(Game* gamePtr, double health, int power, int attackCapacity)
    : HealableUnit(gamePtr, UnitType::ET, health, power, attackCapacity)
{
    isAttackingSoldiers = false;
}

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

bool EarthTank::attack()
{
    LinkedQueue<Unit*> monsterEnemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AM, attackCapacity);
    LinkedQueue<Unit*> soldierEnemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AS, attackCapacity);

    willAttackSoldiers();

    // Check for a successful attack
    bool attackCheck = false;

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    for (int i = 0; i < attackCapacity; i++)
    {
        if (isAttackingSoldiers)
            i % 2 == 0 ? soldierEnemyList.dequeue(enemyUnit) : monsterEnemyList.dequeue(enemyUnit); // Divide attack capacity 50 50
        else
            monsterEnemyList.dequeue(enemyUnit); // Only attack soldiers

        if (!enemyUnit)
            continue;

        // Calculate the UAP and apply the damage
        enemyUnit->receiveDamage(calcUAP(enemyUnit));

        // Check if the unit is dead or can join the battle
        if (enemyUnit->isDead()) 
            gamePtr->addToKilledList(enemyUnit); 
        else
            gamePtr->addUnit(enemyUnit); 

        // Store the IDs of the fought units to be printed later
        foughtUnits.enqueue(enemyUnit->getId()); 

        // Nullify the pointer to avoid duplication
        enemyUnit = nullptr;

        attackCheck = true;
    }

    // Re-adding extra units -if any- to their original lists
    Unit* tempUnitPtr = nullptr;
    while (monsterEnemyList.dequeue(tempUnitPtr))
        gamePtr->addUnit(tempUnitPtr);

    while (soldierEnemyList.dequeue(tempUnitPtr)) 
        gamePtr->addUnit(tempUnitPtr); 

    return attackCheck;
}

bool EarthTank::willAttackSoldiers()
{
    int soldiersRatio = gamePtr->getUnitsCount(ALIEN, AS) > 0 ? gamePtr->getUnitsCount(EARTH, ES) / gamePtr->getUnitsCount(ALIEN, AS) : -1;

    if (soldiersRatio < 0.3 && soldiersRatio >= 0)
        isAttackingSoldiers = true;
    else if (soldiersRatio > 0.8)
        isAttackingSoldiers = false;

    return isAttackingSoldiers;
}

int EarthTank::getHealPriority() const
{
    return 0; // 0 to make soldiers the priority to be healed first in the game and tanks be in the order of adding them
}