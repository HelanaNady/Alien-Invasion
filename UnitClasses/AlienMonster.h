#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H

#include "Unit.h"
#include "../DEFS.h"

class AlienMonster: public Unit
{
public:
	AlienMonster(Game*, double, int, int);

	void printFought(); // Print the units that the monster has fought
	void attack(); // Attack the enemy units
};

#endif