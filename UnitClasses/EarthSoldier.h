#ifndef EARTH_SOLDIER_H
#define EARTH_SOLDIER_H

#include "Unit.h"
class EarthSoldier : public Unit
{
public:
	void print();
	void attack(Unit* aUnit);
};
#endif
