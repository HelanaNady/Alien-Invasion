#include "Army.h"

void Army::printFightingUnits()
{
	Unit* unit;

	while (!currentFighters.isEmpty())
	{
		currentFighters.dequeue(unit);
		unit->print();
	}
}
