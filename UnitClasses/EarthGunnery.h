#ifndef EARTH_GUNNERY_H
#define EARTH_GUNNERY_H

#include "Unit.h"
#include "../DEFS.h"

class EarthGunnery: public Unit
{
public:
	EarthGunnery(Game*, double, int, int);

	void printFought(); // Print the units that the gunnery has fought
	void attack(); // Attack the enemy units

	// Getters
	int getPriority() const; // Get the priority of the gunnery to be used for attacking/picking
};

#endif