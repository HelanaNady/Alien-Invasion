#include "AlienDrone.h"

AlienDrone::AlienDrone(Game* gamePtr, int health, int power, int attackCapacity): Unit(gamePtr, UnitType::AD, health, power, attackCapacity)
{}

void AlienDrone::print() const
{}

void AlienDrone::attack(Unit* aUnit)
{}
