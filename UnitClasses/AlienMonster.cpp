#include "AlienMonster.h"
#include "../Game.h"

AlienMonster::AlienMonster(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AM, health, power, attackCapacity)
{}

void AlienMonster::print() const
{
    if (!foughtUnits.isEmpty())
    {
        std::cout << "AM " << getId() << " shots [";
        foughtUnits.printList();
        std::cout << "]\n";
    }
}

void AlienMonster::attack()
{
    // Get the counts of available units
    int availableSoldiersCount = gamePtr->getUnitsCount(ArmyType::EARTH, UnitType::ES);
    int availableTanksCount = gamePtr->getUnitsCount(ArmyType::EARTH, UnitType::ET);

    // Calculate the attack capacity for soldiers and tanks
    int soldiersAttackCapacity = std::min(availableSoldiersCount, attackCapacity / 2);
    int remainingAttackCapacity = attackCapacity - soldiersAttackCapacity;
    int tanksAttackCapacity = std::min(availableTanksCount, remainingAttackCapacity);

    // If there's still remaining attack capacity add it to soldiers attack capacity
    if (tanksAttackCapacity < remainingAttackCapacity)
        soldiersAttackCapacity += std::min(availableSoldiersCount - soldiersAttackCapacity, remainingAttackCapacity - tanksAttackCapacity);

    // Get the lists of soldiers and tanks
    LinkedQueue<Unit*> soldiersList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ES, soldiersAttackCapacity);
    LinkedQueue<Unit*> tanksList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ET, tanksAttackCapacity);

    LinkedQueue<Unit*> soldiersTempList;
    ArrayStack<Unit*> tanksTempList;
    Unit* enemyUnit = nullptr;

    // Loop through the tanks and soldiers lists
    for (int i = 0; i < 2; i++)
    {
        LinkedQueue<Unit*>& currentList = (i == 0) ? soldiersList : tanksList;

        while (!currentList.isEmpty())
        {
            // Get the unit and remove it from the list
            currentList.dequeue(enemyUnit);

            // Set the first attack time if it's the first time attacking
            if (enemyUnit->isFirstAttack())
                enemyUnit->setFirstTimeAttack(gamePtr->getCurrentTimestep());

            // Receive damage and check whether it's dead or not
            enemyUnit->receiveDamage(calcUAP(enemyUnit));
            if (enemyUnit->isDead())
                gamePtr->killUnit(enemyUnit);
            else
            {
                if (i == 0)
                    soldiersTempList.enqueue(enemyUnit);
                else
                    tanksTempList.push(enemyUnit);
            }

            // Store the IDs of the fought units to be printed later
            foughtUnits.enqueue(enemyUnit->getId());
        }
    }

    // Empty the tempList and re-add the alive units back to their lists
    Unit* unit = nullptr;
    while (soldiersTempList.dequeue(unit))
        gamePtr->addUnit(unit);

    while (tanksTempList.pop(unit))
        gamePtr->addUnit(unit);
}