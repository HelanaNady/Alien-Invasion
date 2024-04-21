#ifndef ALIEN_DRONE_H
#define ALIEN_DRONE_H

#include "Unit.h"
#include "../DEFS.h"

class AlienDrone: public Unit
{
public:
	AlienDrone(Game*, int, int, int);
	void printFought();
	void attack();
};

#endif