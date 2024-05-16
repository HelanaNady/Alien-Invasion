#ifndef ALIEN_DRONE_H
#define ALIEN_DRONE_H

#include "Unit.h"
#include "../DEFS.h"

class AlienDrone: public Unit
{
public:
	AlienDrone(Game*, double, int, int);

	void printUnit(); // Print the unit's type along with its ID
	bool attack(); // Attack the enemy units
};

#endif