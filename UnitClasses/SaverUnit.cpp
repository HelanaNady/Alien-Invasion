#include <iostream>

#include "SaverUnit.h"
#include "../Game.h"

SaverUnit::SaverUnit(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::SU, health, power, attackCapacity)
{}

void SaverUnit::printUnit()
{
    std::cout << "SU " << id;
}

bool SaverUnit::attack()
{
    // Get the lists of alien soldiers to attack
    LinkedQueue<Unit*> enemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AS, attackCapacity);

    std::string foughtUnits = "";

    // Check for a successful attack
    bool attackCheck = false;

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    while (enemyList.dequeue(enemyUnit))
    {
        // Calculate the UAP and apply the damage
        enemyUnit->receiveDamage(calcUAP(enemyUnit));

        // Check if the unit is dead or can join the battle
        if (enemyUnit->isDead())
            gamePtr->addToKilledList(enemyUnit);
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
