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

void AlienDrone::attack()
{
    // Attack capacity is divided 50:50 between them 
    int ETnumber = attackCapacity / 2;
    int EGnumber = attackCapacity - ETnumber;

    LinkedQueue<Unit*> ETlist = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ET, ETnumber);
    LinkedQueue<Unit*> EGlist = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::EG, EGnumber);

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    for (int i = 0; i < attackCapacity; i++)
    {
        // Get the unit and remove it from the list
        if (i % 2 == 0)
            ETlist.dequeue(enemyUnit);
        else
            EGlist.dequeue(enemyUnit);

        if (!enemyUnit)
            continue;

        // Set the first attack time if it's the first time attacking
        if (enemyUnit->isFirstAttack())
            enemyUnit->setFirstTimeAttack(gamePtr->getCurrentTimestep());

        // Receive damage and check whether it's dead or not
        enemyUnit->receiveDamage(calcUAP(enemyUnit));

        if (enemyUnit->isDead())
            gamePtr->addToKilledList(enemyUnit);
        else if (enemyUnit->needsHeal())
            gamePtr->addUnitToMaintenanceList(enemyUnit);
        else
            gamePtr->addUnit(enemyUnit);

        // Store the IDs of the fought units to be printed later
        foughtUnits.enqueue(enemyUnit->getId());
    }
}