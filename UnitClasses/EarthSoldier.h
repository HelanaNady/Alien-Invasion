#ifndef EARTH_SOLDIER_H
#define EARTH_SOLDIER_H

#include "Unit.h"
#include "../DEFS.h"

class EarthSoldier : public Unit
{
public:
	EarthSoldier(UnitType, int, int, int);
	void print();
	void attack(Unit*);
};
#endif
