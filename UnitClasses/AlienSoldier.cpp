#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AS, health, power, attackCapacity)
{}

void AlienSoldier::print() const
{
    std::cout << "AD " << this->getId() << " shots [";
    foughtUnits.printList();
    std::cout << "]\n";
}

void AlienSoldier::attack()
{}
