#include "AlienDrone.h"
#include "../Game.h"

AlienDrone::AlienDrone(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AD, health, power, attackCapacity)
{}

void AlienDrone::printUnit()
{
    std::cout << "AD " << id;
}

bool AlienDrone::attack()
{
    // Attack capacity is divided 50:50 between them
    int ETnumber = attackCapacity / 2;
    int EGnumber = attackCapacity - ETnumber;

    // Get the lists of units to attack
    LinkedQueue<Unit*> ETlist = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ET, ETnumber);
    LinkedQueue<Unit*> EGlist = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::EG, EGnumber);

    std::string foughtUnits = "";

    // Check for a successful attack
    bool attackCheck = false;

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    while (ETlist.dequeue(enemyUnit) || EGlist.dequeue(enemyUnit))
    {
        // Calculate the UAP and apply the damage
        enemyUnit->receiveDamage(calcUAP(enemyUnit));

        // Check if the unit is dead, needs healing or can join the battle
        if (enemyUnit->isDead())
            gamePtr->addToKilledList(enemyUnit);
        else if (enemyUnit->needsHeal())
            gamePtr->addUnitToMaintenanceList(dynamic_cast<HealableUnit*>(enemyUnit));
        else
            gamePtr->addUnit(enemyUnit);

        // Store the IDs of the fought units to be printed later
        if (foughtUnits != "")
            foughtUnits += ", ";
        foughtUnits += std::to_string(enemyUnit->getId());

        // Nullify the pointer
        enemyUnit = nullptr;

        // If this line is reached, at least one unit was attacked
        attackCheck = true;
    }

    if (foughtUnits != "")
        gamePtr->registerAttack(this, "shots", foughtUnits);

    return attackCheck;
}