#ifndef EARTH_TANK_H
#define EARTH_TANK_H

#include "HealableUnit.h"
#include "../DEFS.h"

class EarthTank: public HealableUnit
{
public:
	EarthTank(Game*, double, int, int);
	void printFought(); // Print the units that the tank has fought
	bool attack(); // Attack the enemy units

	// Getters
	int getHealPriority() const;  // Get the heal priority of the soldier to be used in the UML
};

#endif