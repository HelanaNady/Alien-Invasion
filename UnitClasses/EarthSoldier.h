#ifndef EARTH_SOLDIER_H
#define EARTH_SOLDIER_H

#include "Unit.h"
#include "../DEFS.h"

class EarthSoldier: public Unit
{
public:
	EarthSoldier(Game*, double, int, int);
	void printFought();
	void attack();
	int getHealPriority() const;
};

#endif