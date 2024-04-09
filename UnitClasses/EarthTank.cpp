#include "EarthTank.h"

EarthTank::EarthTank(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::ET, health, power, attackCapacity)
{}

void EarthTank::print() const
{
    std::cout << "ET " << this->getId() << " shots [";
    foughtUnits.printList();
    std::cout << "]\n";
}

void EarthTank::attack(Unit* aUnit)
{}
