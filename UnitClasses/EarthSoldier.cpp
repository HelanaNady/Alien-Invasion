#include "EarthSoldier.h"

EarthSoldier::EarthSoldier(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::ES, health, power, attackCapacity)
{}

void EarthSoldier::print() const
{}

void EarthSoldier::attack()
{}
