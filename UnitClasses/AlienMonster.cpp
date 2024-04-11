#include "AlienMonster.h"

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
{}
