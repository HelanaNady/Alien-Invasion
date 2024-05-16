#include "EarthSoldier.h"
#include "../Game.h"
#include "../Containers/LinkedQueue.h"

EarthSoldier::EarthSoldier(Game* gamePtr, double health, int power, int attackCapacity)
    : HealableUnit(gamePtr, UnitType::ES, health, power, attackCapacity), infected(false), immune(false)
{}

void EarthSoldier::printUnit()
{
    std::cout << "ES " << id;
    if (infected)
        std::cout << "*";
}

bool EarthSoldier::attack()
{
    std::string foughtUnits = "";
    // Check if the unit is infected and decide what to attack
    ArmyType enemyArmyType = isInfected() ? ArmyType::EARTH : ArmyType::ALIEN;
    UnitType enemyUnitType = isInfected() ? UnitType::ES : UnitType::AS;

    // Get the lists of units to attack
    LinkedQueue<Unit*> enemyList = gamePtr->getEnemyList(enemyArmyType, enemyUnitType, attackCapacity);

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

bool EarthSoldier::getInfection()
{
    if (isInfected() || isImmune())
        return false;

    infected = true; // Set the infected flag to true

    return true;
}

bool EarthSoldier::isInfected() const
{
    return infected;
}

void EarthSoldier::loseInfection()
{
    infected = false; // Set the infected flag to false since the unit is healed
}

void EarthSoldier::gainImmunity()
{
    immune = true; // Set the immunity flag to true
}

bool EarthSoldier::isImmune() const
{
    return immune;
}

int EarthSoldier::getHealPriority() const
{
    return 100 - (int) health; // The lower the health, the higher the priority
};
