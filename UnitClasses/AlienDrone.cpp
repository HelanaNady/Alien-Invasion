#include "AlienDrone.h"
#include "../Game.h"

AlienDrone::AlienDrone(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AD, health, power, attackCapacity)
{}

void AlienDrone::print()
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "AD " << getId() << " shots [";
        foughtUnits.printList();
        std::cout << "]" << std::endl;

        clearFoughtUnits(); // Clear the list after printing
    }
}

void AlienDrone::attack()
{
    int ETnumber = (attackCapacity / 2) + 1;
    int EGnumber = attackCapacity - ETnumber;

    LinkedQueue<Unit*> ETlist = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ET, ETnumber);
    LinkedQueue<Unit*> EGlist = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::EG, EGnumber);

    ArrayStack<Unit*> ETtempList;
    LinkedQueue<Unit*> EGtempList;

    for (int i = 0; i < attackCapacity; i++)
    {
        Unit* attackedUnit = nullptr;

        // Get the unit and remove it from the list
        if (i % 2 == 0)
            ETlist.dequeue(attackedUnit);
        else
            EGlist.dequeue(attackedUnit);

        if (!attackedUnit)
            continue;

        // Set the first attack time if it's the first time attacking
        if (attackedUnit->isFirstAttack())
            attackedUnit->setFirstTimeAttack(gamePtr->getCurrentTimestep());

        // Receive damage and check whether it's dead or not
        attackedUnit->receiveDamage(calcUAP(attackedUnit));

        if (attackedUnit->isDead())
            gamePtr->addToKilledList(attackedUnit);
        else
        {
            UnitType unitType = attackedUnit->getUnitType();

            switch (unitType)
            {
                case UnitType::ET:
                    ETtempList.push(attackedUnit);
                    break;

                case UnitType::EG:
                    EGtempList.enqueue(attackedUnit);
                    break;
            }
        }

        foughtUnits.enqueue(attackedUnit->getId());
    }

    // Empty the tempList and re-add the alive units back to their lists
    Unit* unit = nullptr;
    while (ETtempList.pop(unit))
        gamePtr->addUnit(unit);

    while (EGtempList.dequeue(unit))
        gamePtr->addUnit(unit);
}