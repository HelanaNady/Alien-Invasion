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
    // Get the number of units to attack
    int AMnumber = attackCapacity;
    int ADnumber = attackCapacity;

    // Get the lists of units to attack
    LinkedQueue<Unit*> AMlist = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AM, AMnumber);
    LinkedQueue<Unit*> ADlist = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AD, ADnumber);

    // Check for a successful attack
    bool attackCheck = false;

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    // Counter to handle attacking 2 drones then a monster repeatedly
    int dronesCount = 2;

    for (int i = 0; i < 3 * attackCapacity; i++)
    {
        if (dronesCount == 0) // If the gunnery attacked 2 drones, attack a monster
        {
            AMlist.dequeue(enemyUnit);
            dronesCount = 2; // Reseting the counter
        }
        else // If the gunnery didn't attack 2 drones yet, attack a drone
        {
            ADlist.dequeue(enemyUnit);
            dronesCount--;
        }

        // Check if the unit is a nullptr
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

        // If this line is reached, at least one unit was attacked
        attackCheck = true;
    }

    // Empty rest of enemy list
    Unit* unit = nullptr;
    while (AMlist.dequeue(unit))
        gamePtr->addUnit(unit);

    while (ADlist.dequeue(unit))
        gamePtr->addUnit(unit);

    return attackCheck;
}

int EarthGunnery::getPriority() const
{
    return (int) getHealth() + getPower();
}