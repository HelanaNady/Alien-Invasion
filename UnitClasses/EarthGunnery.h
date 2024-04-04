#ifndef EARTH_GUNNERY_H
#define EARTH_GUNNERY_H

#include "Unit.h"
#include "../DEFS.h"

class EarthGunnery: public Unit
{
public:
	EarthGunnery(UnitType, int, int, int);
	void print();
	void attack(Unit* aUnit);
};
#endif

