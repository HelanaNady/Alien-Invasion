#include "EarthGunnery.h"
#include "../Game.h"

EarthGunnery::EarthGunnery(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EG, health, power, attackCapacity)
{}

void EarthGunnery::print() const
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "EG " << getId() << " shots [";
        foughtUnits.printList();
        std::cout << "]\n";
    }
}

void EarthGunnery::attack()
{
    int AMnumber = (attackCapacity / 2) + 1;
    int ADnumber = attackCapacity - AMnumber;


    LinkedQueue<Unit*> AMlist = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AM, AMnumber);
    LinkedQueue<Unit*> ADlist = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AD, ADnumber);

    LinkedQueue<Unit*> tempList;

    int dronesCount = 2; // Counter to handle attacking 2 drones then a monster repeatedly

    for (int i = 0; i < attackCapacity; i++)
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
            gamePtr->killUnit(attackedUnit);
        else
            tempList.enqueue(attackedUnit);

        // Store the IDs of the fought units to be printed later
        foughtUnits.enqueue(attackedUnit->getId());
    }

    // Empty the tempList and re-add the alive units back to their lists
    Unit* unit = nullptr;
    while (tempList.dequeue(unit))
        gamePtr->addUnit(unit);
}

int EarthGunnery::getPriority() const
{
    return getHealth() + getPower();
}