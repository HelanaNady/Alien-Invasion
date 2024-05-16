#ifndef SAVER_UNIT_H
#define SAVER_UNIT_H

#include "Unit.h"
#include "../DEFS.h"

class SaverUnit: public Unit
{
public:
	SaverUnit(Game*, double, int, int);

	void printUnit(); // Print the unit's type along with its ID
	bool attack(); // Attack the enemy units
};

#endif