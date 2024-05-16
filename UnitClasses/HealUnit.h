#ifndef HEAL_UNIT_H
#define HEAL_UNIT_H

#include "../UnitClasses/Unit.h"
#include "../UnitClasses/EarthSoldier.h"
#include "../DEFS.h"

class HealUnit: public Unit
{
public:
	HealUnit(Game*, double, int, int);

	void printUnit();
	bool attack(); // Heal units from the unit maintenance list

	void healInfection(EarthSoldier*); // Heal the infection of the soldier
};

#endif