#include "EarthGunnery.h"
#include "../Game.h"

EarthGunnery::EarthGunnery(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EG, health, power, attackCapacity)
{}

void EarthGunnery::printUnit()
{
    std::cout << "EG " << id;
}

bool EarthGunnery::attack()
{
    int dronesCapacity = attackCapacity / 2;

    // To ensure that drones will be attacked in pairs 
    if (dronesCapacity % 2 && attackCapacity > 2) dronesCapacity++;

    int monstersCapacity = attackCapacity - dronesCapacity;

    LinkedQueue<Unit*> dronesList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AD, dronesCapacity);
    LinkedQueue<Unit*> monstersList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AM, monstersCapacity);

    std::string foughtUnits = "";

    // Check for a successful attack
    bool attackCheck = false;

    // Create a pointer to the enemy list
    Unit* enemyUnit = nullptr;

    while (dronesList.dequeue(enemyUnit) || monstersList.dequeue(enemyUnit))
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

int EarthGunnery::getPriority() const
{
    return (int) getHealth() + getPower();
}