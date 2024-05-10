#include <cmath>

#include "EarthTank.h"
#include "../Game.h"
#include "../Containers/LinkedQueue.h"

bool EarthTank::isAttackingSoldiers = false;

EarthTank::EarthTank(Game* gamePtr, double health, int power, int attackCapacity)
    : HealableUnit(gamePtr, UnitType::ET, health, power, attackCapacity)
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

bool EarthTank::attack()
{
    // If the tank is attacking soldiers, divide the attack capacity 50-50 between soldiers and monsters
    int soldiersAttackCapacity = willAttackSoldiers() ? attackCapacity / 2 : 0; 
    int monstersAttackCapacity = attackCapacity - soldiersAttackCapacity;

    // Get the lists of alien soldiers and monsters to attack
    LinkedQueue<Unit*> monsterEnemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AM, monstersAttackCapacity);
    LinkedQueue<Unit*> soldierEnemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AS, soldiersAttackCapacity);

    // Check for a successful attack
    bool attackCheck = false;

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    while (monsterEnemyList.dequeue(enemyUnit) || soldierEnemyList.dequeue(enemyUnit))
    {
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

        // Set attack check to true if one unit at least was attacked successfully
        attackCheck = true;
    }

    return attackCheck;
}

bool EarthTank::willAttackSoldiers()
{
    float soldiersRatio = gamePtr->getUnitsCount(ALIEN, AS) > 0 ? (float) gamePtr->getUnitsCount(EARTH, ES) / gamePtr->getUnitsCount(ALIEN, AS) : -1;

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