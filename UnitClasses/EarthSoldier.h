#ifndef EARTH_SOLDIER_H
#define EARTH_SOLDIER_H

#include "HealableUnit.h"
#include "../DEFS.h"

class EarthSoldier: public HealableUnit
{
private:
	bool infected; // If the soldier is infected or not

public:
	EarthSoldier(Game*, double, int, int);
	void printFought(); // Print the units that the soldier has fought
	bool attack(); // Attack the enemy units

	// Infection functions
	void infect(); // Infect the soldier
	bool isInfected() const; // Check if the soldier is infected

	// Getters
	int getHealPriority() const; // Get the heal priority of the soldier to be used in the UML
};

#endif