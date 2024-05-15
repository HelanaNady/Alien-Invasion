#ifndef EARTH_TANK_H
#define EARTH_TANK_H

#include "HealableUnit.h"
#include "../DEFS.h"

class EarthTank: public HealableUnit
{
private:
	static bool isAttackingSoldiers; // A flag to check if the tank is attacking soldiers in the current timestep

public:
	EarthTank(Game*, double, int, int);

	void printFought(); // Print the units that the tank has fought
	bool attack(); // Attack the enemy units

	bool willAttackSoldiers(); // Check if the tank will attack soldiers in the current timestep

	// Getters
	int getHealPriority() const; // Get the heal priority of the tank to be used in the UML
};

#endif