#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EG, health, power, attackCapacity)
{}

void EarthGunnery::print() const
{
    std::cout << "EG " << this->getId() << " shots [";
    foughtUnits.printList();
    std::cout << "]\n";
}

void EarthGunnery::attack(Unit* aUnit)
{}

int EarthGunnery::getPriority() const
{
    return getHealth() + getPower();
}