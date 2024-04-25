#ifndef ALIEN_DRONE_H
#define ALIEN_DRONE_H

#include "Unit.h"
#include "../DEFS.h"

class AlienDrone: public Unit
{
public:
	AlienDrone(Game*, double, int, int);
	void printFought(); // Print the units that the drone has fought
	void attack(); // Attack the enemy units

};

#endif