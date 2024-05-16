#include "AlienMonster.h"
#include "../Game.h"

int AlienMonster::infectingProbability = 0;

AlienMonster::AlienMonster(Game* gamePtr, double health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AM, health, power, attackCapacity)
{}

void AlienMonster::setInfectingProbability(int probability)
{
    infectingProbability = probability;
}

void AlienMonster::printUnit()
{
    std::cout << "AM " << this;
}

void AlienMonster::printFought()
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "AM " << getId() << " shots [";
        foughtUnits.printList();
        std::cout << "]" << std::endl;

        clearFoughtUnits(); // Clear the list after printing
    }
}

bool AlienMonster::attack()
{
    // Calculate the number of soldiers and tanks to attack
    int soldiersCapacity = attackCapacity / 3;
    int tanksCapacity = attackCapacity / 3;
    int saversCapacity = attackCapacity - soldiersCapacity - tanksCapacity;

    // Get the lists of earth soldiers and tanks to attack
    LinkedQueue<Unit*> soldiersList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ES, soldiersCapacity);
    LinkedQueue<Unit*> tanksList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ET, tanksCapacity);
    LinkedQueue<Unit*> saversList = gamePtr->getEnemyList(ArmyType::EARTH_ALLIED, UnitType::SU, saversCapacity);

    // Check for a successful attack
    bool attackCheck = false;

    // Create a pointer to the enemy unit
    Unit* enemyUnit = nullptr;

    // Loop through the tanks and soldiers lists
    while (soldiersList.dequeue(enemyUnit) || tanksList.dequeue(enemyUnit) || saversList.dequeue(enemyUnit))
    {
        // Check if the enemy unit is an Earth Soldier and infect it if the probability is met
        int x = rand() % 100 + 1;
        if (enemyUnit->getUnitType() == UnitType::ES && x <= infectingProbability)
        {
            dynamic_cast<EarthSoldier*>(enemyUnit)->getInfection(); // The soldier will get infected if not infected already and not immune
            gamePtr->addUnit(enemyUnit); // The soldier will be re-enqueued to the list & infected soldiers counter will be incremented
            continue;
        }

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
        foughtUnits.enqueue(enemyUnit->getId());

        // Nullify the pointer
        enemyUnit = nullptr;

        // If this line is reached, at least one unit was attacked
        attackCheck = true;
    }

    return attackCheck;
}