#include "EarthSoldier.h"
#include "../Game.h"
#include "../Containers/LinkedQueue.h"

EarthSoldier::EarthSoldier(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::ES, health, power, attackCapacity)
{}

void EarthSoldier::printFought()
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "ES " << getId() << " shots [";
        foughtUnits.printList();
        std::cout << "]" << std::endl;

        clearFoughtUnits(); // Clear the list after printing
    }
}

bool EarthSoldier::attack()
{
    // Get the lists of earth soldiers to attack
    LinkedQueue<Unit*> enemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AS, attackCapacity);

    // Check for a successful attack
    bool attackCheck = !enemyList.isEmpty();

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    while (enemyList.dequeue(enemyUnit))
    {
        // Check if it were attacked before or not
        if (enemyUnit->isFirstAttack())
            enemyUnit->setFirstTimeAttack(gamePtr->getCurrentTimestep());

        // Receive damage and check: if dead -> add to killed list else -> add to its army back
        enemyUnit->receiveDamage(calcUAP(enemyUnit));
        if (enemyUnit->isDead())
            gamePtr->addToKilledList(enemyUnit);
        else
            gamePtr->addUnit(enemyUnit);

        // Store the IDs of the fought units to be printed later
        foughtUnits.enqueue(enemyUnit->getId());
    }
    return attackCheck;

}
