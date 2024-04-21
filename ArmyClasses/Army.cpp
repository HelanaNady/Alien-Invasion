#include "Army.h"

void Army::printFightingUnits()
{
	Unit* unit = nullptr;

	while (currentAttackers.dequeue(unit))
		unit->printFought();
}
