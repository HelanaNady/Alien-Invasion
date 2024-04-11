#include "Army.h"

void Army::printFightingUnits()
{
	Unit* unit;

	while (!currentAttackers.isEmpty())
	{
		currentAttackers.dequeue(unit);
		unit->print();
	}
}
