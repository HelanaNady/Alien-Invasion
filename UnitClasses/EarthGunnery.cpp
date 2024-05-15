#include "EarthGunnery.h"
#include "../Game.h"

EarthGunnery::EarthGunnery(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EG, health, power, attackCapacity)
{}

void EarthGunnery::printFought()
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "EG " << getId() << " shots [";
        foughtUnits.printList();
        std::cout << "]" << std::endl;

        clearFoughtUnits(); // Clear the list after printing
    }
}

bool EarthGunnery::attack()
{
    int dronesCapacity = attackCapacity / 2;

    // To ensure that drones will be attacked in pairs 
    if (dronesCapacity % 2 && attackCapacity > 2) dronesCapacity++;

    int monstersCapacity = attackCapacity - dronesCapacity;

    LinkedQueue<Unit*> dronesList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AD, dronesCapacity);
    LinkedQueue<Unit*> monstersList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AM, monstersCapacity);

    // Check for a successful attack
    bool attackCheck = false;

    // Create a pointer to the enemy list
    Unit* enemyUnit = nullptr;

    while (dronesList.dequeue(enemyUnit) || monstersList.dequeue(enemyUnit))
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

        // If this line is reached, at least one unit was attacked
        attackCheck = true;
    }
    return attackCheck;
}

int EarthGunnery::getPriority() const
{
    return (int) getHealth() + getPower();
}