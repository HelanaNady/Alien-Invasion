#include "EarthTank.h"
#include "../Game.h"
#include "../Containers/LinkedQueue.h"

EarthTank::EarthTank(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::ET, health, power, attackCapacity)
{}

void EarthTank::print() const
{
    std::cout << "ET " << this->getId() << " shots [";
    foughtUnits.printList();
    std::cout << "]\n";
}

void EarthTank::attack()
{
    LinkedQueue<Unit*> monsterEnemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AM, attackCapacity); 
    LinkedQueue<Unit*> soldierEnemyList = gamePtr->getEnemyList(ArmyType::ALIEN, UnitType::AS, attackCapacity); 








}
