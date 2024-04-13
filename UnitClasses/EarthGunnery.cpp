#include "EarthGunnery.h"
#include "../Game.h"

EarthGunnery::EarthGunnery(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EG, health, power, attackCapacity)
{}

void EarthGunnery::print() const
{
    std::cout << "EG " << this->getId() << " shots [";
    foughtUnits.printList();
    std::cout << "]\n";
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

        if (!attackedUnit && (!AMlist.isEmpty() || !ADlist.isEmpty()))
        {
            i--;
            continue;
        }

        // Check if it was attacked before or not
        if (attackedUnit->getFirstAttackTime() == -1)
            attackedUnit->setFirstTimeAttack(gamePtr->getCurrentTimestep());

        // Decrement health 
        attackedUnit->recieveDamage(calcUAP(attackedUnit));

        // Check if it was killed or not
        if (attackedUnit->getHealth())
        {
            tempList.enqueue(attackedUnit);
        }
        else
        {
            gamePtr->killUnit(attackedUnit);
            attackedUnit->setDestructionTime(gamePtr->getCurrentTimestep());
            attackedUnit->setDestructionDelay();
            attackedUnit->setBattleDelay();
        }

        foughtUnits.enqueue(attackedUnit->getId());
    }

    // Re-adding attacked units to their original lists
    Unit* unit = nullptr;
    while (tempList.dequeue(unit))
        gamePtr->addUnit(unit);
}

int EarthGunnery::getPriority() const
{
    return getHealth() + getPower();
}