#include "AlienMonster.h"
#include "Game.h"

AlienMonster::AlienMonster(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AM, health, power, attackCapacity)
{}

void AlienMonster::print() const
{
    std::cout << "AM " << this->getId() << " shots [";
    foughtUnits.printList();
    std::cout << "]\n";
}

void AlienMonster::attack()
{
    int soldiersCapacity = attackCapacity / 2;
    int tanksCapacity = attackCapacity - tanksCapacity;

    LinkedQueue<Unit*> soldiersList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ES, soldiersCapacity);
    LinkedQueue<Unit*> tanksList = gamePtr->getEnemyList(ArmyType::EARTH, UnitType::ET, tanksCapacity);

    LinkedQueue<Unit*> tempList;
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
            if (enemyUnit->getFirstAttackTime() == -1)
            {
                enemyUnit->setFirstTimeAttack(gamePtr->getCurrentTimestep());
                enemyUnit->setFirstAttackDelay();
            }

            // Receive damage and check whether it's dead or not
            enemyUnit->recieveDamage(this->calcUAP(enemyUnit));
            if (enemyUnit->getHealth() == 0)
            {
                gamePtr->killUnit(enemyUnit);
                enemyUnit->setDestructionTime(gamePtr->getCurrentTimestep());
                enemyUnit->setDestructionDelay();
                enemyUnit->setBattleDelay();
            }
            else
                tempList.enqueue(enemyUnit);

            // Store the IDs of the fought units to be printed later
            foughtUnits.enqueue(enemyUnit->getId());
        }
    }

    // Empty the tempList and re-add the alive units back to their lists
    while (!tempList.isEmpty())
    {
        Unit* tempUnitPtr = nullptr;
        tempList.dequeue(tempUnitPtr);
        gamePtr->addUnit(tempUnitPtr);
    }
}