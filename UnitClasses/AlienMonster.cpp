#include "AlienMonster.h"

AlienMonster::AlienMonster(Game* gamePtr, int health, int power, int attackCapacity): Unit(gamePtr, UnitType::AM, health, power, attackCapacity)
{}

void AlienMonster::print() const
{}

void AlienMonster::attack(Unit* aUnit)
{}
