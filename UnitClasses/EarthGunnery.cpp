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


    LinkedQueue<Unit*> AMlist = gamePtr->getEnemyList(ALIEN, AM, AMnumber);
    LinkedQueue<Unit*> ADlist = gamePtr->getEnemyList(ALIEN, AD, ADnumber);

    LinkedQueue<Unit*> AMtempList;
    LinkedQueue<Unit*> ADtempList;

    int dronesCount = 2; // Counter to handle attacking 2 drones then a monster repeatedly

    for (int i = 0; i < attackCapacity; i++)
    {
        Unit* attackedUnit = nullptr;

        if (dronesCount == 0)
        {
            ADlist.dequeue(attackedUnit);
            dronesCount = 2; // Reset counter
        }
        else
        {
            AMlist.dequeue(attackedUnit);
            dronesCount--;
        }

        if (!attackedUnit)
            continue;

        // Check if it was attacked before or not
        if (attackedUnit->getTattack() == -1)
            setTattack(gamePtr->getCurrentTimestep());

        // Decrement health 
        attackedUnit->recieveDamage(calcUAP(attackedUnit));

        // Check if it was killed or not
        if (attackedUnit->getHealth())
        {
            UnitType unitType = attackedUnit->getUnitType();

            switch (unitType)
            {
                case UnitType::AM:
                    AMtempList.enqueue(attackedUnit);
                    break;

                case UnitType::AD:
                    ADtempList.enqueue(attackedUnit);
                    break;
            }
        }
        else
        {
            gamePtr->killUnit(attackedUnit);
            attackedUnit->setTdestruction(gamePtr->getCurrentTimestep());
            attackedUnit->setDdestruction();
            attackedUnit->setDbattle();
        }

        foughtUnits.enqueue(attackedUnit->getId());
    }

    // Re-adding attacked units to their original lists
    while (!AMtempList.isEmpty())
    {
        Unit* unit;
        AMtempList.dequeue(unit);
        gamePtr->addUnit(unit);
    }

    while (!ADtempList.isEmpty())
    {
        Unit* unit;
        ADtempList.dequeue(unit);
        gamePtr->addUnit(unit);
    }
}

int EarthGunnery::getPriority() const
{
    return getHealth() + getPower();
}