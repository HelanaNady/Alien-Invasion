#ifndef EARTH_TANK_H
#define EARTH_TANK_H

#include "Unit.h"
#include "../DEFS.h"

class EarthTank: public Unit
{
public:
	EarthTank(Game*, double, int, int);

	void printFought(); // Print the units that the tank has fought
	void attack(); // Attack the enemy units

	// Getters
	int getHealPriority() const;  // Get the heal priority of the soldier to be used in the UML
};

#endif