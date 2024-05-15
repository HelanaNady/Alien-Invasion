#ifndef HEAL_UNIT_H
#define HEAL_UNIT_H

#include "../UnitClasses/EarthSoldier.h"
#include "../DEFS.h"

class HealUnit: public Unit
{
public:
	HealUnit(Game*, double, int, int);
	void printFought(); // Print the units that the tank has fought
	bool attack(); // Heal units from the unit maintenance list
	void healInfection(EarthSoldier*);
};

#endif