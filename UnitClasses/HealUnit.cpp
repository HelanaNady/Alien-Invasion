#include "HealUnit.h"
#include "../Game.h"

HealUnit::HealUnit(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EH, health, power, attackCapacity)
{}

bool HealUnit::attack()
{}
