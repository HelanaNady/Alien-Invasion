#include "EarthTank.h"

EarthTank::EarthTank(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::ET, health, power, attackCapacity)
{}

void EarthTank::printFought() const
{}

void EarthTank::attack()
{}
