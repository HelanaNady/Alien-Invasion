#include "Army.h"

void Army::printFightingUnits()
{
	Unit* unit;

	while (currentAttackers.dequeue(unit))
		unit->print();
}
