#ifndef EARTH_GUNNERY_H
#define EARTH_GUNNERY_H

#include "Unit.h"
class EarthGunnery: public Unit
{
public:
	void print();
	void attack(Unit* aUnit);
};
#endif

