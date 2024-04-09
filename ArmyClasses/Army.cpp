#include "Army.h"

void Army::printFightingUnits()
{
	Unit* unit;
	while (!currentFightors.isEmpty())
	{
		currentFightors.dequeue(unit);
		unit->print();
	}
}
