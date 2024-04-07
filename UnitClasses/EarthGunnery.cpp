#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(Game* gamePtr, int health, int power, int attackCapacity)
    : Unit(gamePtr, UnitType::EG, health, power, attackCapacity)
{}

void EarthGunnery::print() const
{}

void EarthGunnery::attack(Unit* aUnit)
{}
