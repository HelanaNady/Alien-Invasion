#include "EarthSoldier.h"
#include "../Game.h"
#include "../Containers/LinkedQueue.h"

EarthSoldier::EarthSoldier(Game* gamePtr, double health, int power, int attackCapacity)
    : HealableUnit(gamePtr, UnitType::ES, health, power, attackCapacity), infected(false)
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
    bool attackCheck = false;

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    while (enemyList.dequeue(enemyUnit))
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

void EarthSoldier::infect()
{
    // Set the infected flag to true
    infected = true;

    // Increment the infected earth soldier count
    gamePtr->incrementInfectedESCount();
}

bool EarthSoldier::isInfected() const
{
    return infected;
}

int EarthSoldier::getHealPriority() const
{
    return 100 - (int) health; // The lower the health, the higher the priority
};
