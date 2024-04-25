#ifndef EARTH_TANK_H
#define EARTH_TANK_H

#include "Unit.h"
#include "../DEFS.h"

class EarthTank: public Unit
{
public:
	EarthTank(Game*, double, int, int);
	void printFought();
	void attack();
	int getHealPriority() const;
};

#endif