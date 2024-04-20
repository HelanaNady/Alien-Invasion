#include "EarthGunnery.h"
#include "../Game.h"

EarthGunnery::EarthGunnery(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EG, health, power, attackCapacity)
{}

void EarthGunnery::print()
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


    int dronesCount = 2; // Counter to handle attacking 2 drones then a monster repeatedly

    for (int i = 0; i < 3*attackCapacity; i++)
    {
        Unit* attackedUnit = nullptr;

        if (dronesCount == 0)
        {
            AMlist.dequeue(attackedUnit);
            dronesCount = 2; // Reseting the counter
        }
        else
        {
            ADlist.dequeue(attackedUnit);
            dronesCount--;
        }

        if (!attackedUnit)
        {
            continue;
        }

        // Set the first attack time if it's the first time attacking
        if (attackedUnit->isFirstAttack())
            attackedUnit->setFirstTimeAttack(gamePtr->getCurrentTimestep());

        // Receive damage and check whether it's dead or not
        attackedUnit->receiveDamage(calcUAP(attackedUnit));

        if (attackedUnit->isDead())
            gamePtr->addToKilledList(attackedUnit);
        else
            gamePtr->addUnit(attackedUnit);

        // Store the IDs of the fought units to be printed later
        foughtUnits.enqueue(attackedUnit->getId());
    }

    // Empty rest of enemy list
    Unit* unit = nullptr;
    while (AMlist.dequeue(unit))
        gamePtr->addUnit(unit);

    while(ADlist.dequeue(unit))
        gamePtr->addUnit(unit);
}

int EarthGunnery::getPriority() const
{
    return getHealth() + getPower();
}