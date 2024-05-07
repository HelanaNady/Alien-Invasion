#include "EarthSoldier.h"
#include "../Game.h"
#include "../Containers/LinkedQueue.h"

EarthSoldier::EarthSoldier(Game* gamePtr, double health, int power, int attackCapacity)
    : HealableUnit(gamePtr, UnitType::ES, health, power, attackCapacity)
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
    }

    return attackCheck;
}

int EarthSoldier::getHealPriority() const
{
    return 100 - health; // The lower the health, the higher the priority
};
