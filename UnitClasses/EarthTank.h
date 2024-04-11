#ifndef EARTH_TANK_H
#define EARTH_TANK_H

#include "Unit.h"
#include "../DEFS.h"

class EarthTank: public Unit
{
public:
	EarthTank(Game*, int, int, int);
	void print() const;
	void attack();
};
#endif
