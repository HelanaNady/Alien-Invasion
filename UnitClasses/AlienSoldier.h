#ifndef ALIEN_SOLDIER_H
#define ALIEN_SOLDIER_H

#include "Unit.h"
#include "../DEFS.h"

class AlienSoldier: public Unit
{
public:
	AlienSoldier(Game*, double, int, int);

	void printFought(); // Print the units that the soldier has fought
	void printUnit();
	bool attack(); // Attack the enemy units
};

#endif