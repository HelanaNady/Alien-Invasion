#include "AlienSoldier.h"

AlienSoldier::AlienSoldier(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::AS, health, power, attackCapacity)
{}

void AlienSoldier::printFought() const
{}

void AlienSoldier::attack()
{}
