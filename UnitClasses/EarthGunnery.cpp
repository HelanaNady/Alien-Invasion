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

void EarthGunnery::attack()
{
    int AMnumber = attackCapacity;
    int ADnumber = attackCapacity;

    LinkedQueue<Unit*> AMlist = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AM, AMnumber);
    LinkedQueue<Unit*> ADlist = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AD, ADnumber);

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    int dronesCount = 2; // Counter to handle attacking 2 drones then a monster repeatedly

    for (int i = 0; i < 3 * attackCapacity; i++)
    {
        if (dronesCount == 0)
        {
            AMlist.dequeue(enemyUnit);
            dronesCount = 2; // Reseting the counter
        }
        else
        {
            ADlist.dequeue(enemyUnit);
            dronesCount--;
        }

        if (!enemyUnit)
            continue;

        // Set the first attack time if it's the first time attacking
        if (enemyUnit->isFirstAttack())
            enemyUnit->setFirstTimeAttack(gamePtr->getCurrentTimestep());

        // Receive damage and check whether it's dead or not
        enemyUnit->receiveDamage(calcUAP(enemyUnit));

        if (enemyUnit->isDead())
            gamePtr->addToKilledList(enemyUnit);
        else
            gamePtr->addUnit(enemyUnit);

        // Store the IDs of the fought units to be printed later
        foughtUnits.enqueue(enemyUnit->getId());

        // Reset enemyUnit pointer to nullptr to avoid previous state duplication
        enemyUnit = nullptr;
    }

    // Empty rest of enemy list
    Unit* unit = nullptr;
    while (AMlist.dequeue(unit))
        gamePtr->addUnit(unit);

    while (ADlist.dequeue(unit))
        gamePtr->addUnit(unit);
}

int EarthGunnery::getPriority() const
{
    return getHealth() + getPower();
}