#include "AlienDrone.h"
#include "../Game.h"

AlienDrone::AlienDrone(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AD, health, power, attackCapacity)
{}

void AlienDrone::printFought()
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "AD " << getId() << " shots [";
        foughtUnits.printList();
        std::cout << "]" << std::endl;

        clearFoughtUnits(); // Clear the list after printing
    }
}

bool AlienDrone::attack()
{
    // Attack capacity is divided 50:50 between them 
    int ETnumber = attackCapacity / 2;
    int EGnumber = attackCapacity - ETnumber;

    LinkedQueue<Unit*> ETlist = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ET, ETnumber);
    LinkedQueue<Unit*> EGlist = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::EG, EGnumber);

    bool attackCheck = !(ETlist.isEmpty() && EGlist.isEmpty());

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
            gamePtr->addUnit(attackedUnit);

        // Store the IDs of the fought units to be printed later
        foughtUnits.enqueue(attackedUnit->getId());
    }

    return attackCheck;
}