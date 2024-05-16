#ifndef ALIEN_SOLDIER_H
#define ALIEN_SOLDIER_H

#include "Unit.h"
#include "../DEFS.h"

class AlienSoldier: public Unit
{
public:
	AlienSoldier(Game*, double, int, int);
	
	void printUnit(); // Print the unit's type along with its ID
	bool attack(); // Attack the enemy units
};

#endif