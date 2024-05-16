#ifndef EARTH_GUNNERY_H
#define EARTH_GUNNERY_H

#include "Unit.h"
#include "../DEFS.h"

class EarthGunnery: public Unit
{
public:
	EarthGunnery(Game*, double, int, int);

	void printUnit(); // Print the unit's type along with its ID
	bool attack(); // Attack the enemy units

	// Getters
	int getPriority() const; // Get the priority of the gunnery to be used for attacking/picking
};

#endif