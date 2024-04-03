#ifndef EARTH_TANK_H
#define EARTH_TANK_H

#include "Unit.h"
class EarthTank: public Unit
{
public:
	void print();
	void attack(Unit* aUnit);
};
#endif

