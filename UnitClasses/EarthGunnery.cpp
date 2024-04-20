#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EG, health, power, attackCapacity)
{}

void EarthGunnery::printFought() const
{}

void EarthGunnery::attack()
{}

int EarthGunnery::getPriority() const
{
    return getHealth() + getPower();
}