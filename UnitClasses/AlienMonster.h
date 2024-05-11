#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H

#include "Unit.h"
#include "../DEFS.h"

class AlienMonster: public Unit
{
private:
	static int infectingProbability; // The probability of infecting the enemy units
public:
	AlienMonster(Game*, double, int, int);

	// Static functions
	static void setInfectingProbability(int); // Set the infecting probability

	void printFought(); // Print the units that the monster has fought
	bool attack(); // Attack the enemy units
};

#endif