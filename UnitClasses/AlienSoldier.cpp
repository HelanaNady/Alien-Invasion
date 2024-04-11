#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AS, health, power, attackCapacity)
{}

void AlienSoldier::print() const
{}

void AlienSoldier::attack()
{}
