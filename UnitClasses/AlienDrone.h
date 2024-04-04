#ifndef ALIEN_DRONE_H
#define ALIEN_DRONE_H

#include "Unit.h"
#include "../DEFS.h"

class AlienDrone: public Unit
{
public:
	AlienDrone(UnitType, int, int, int);
	void print();
	void attack(Unit*);
};
#endif
