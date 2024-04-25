#include "Army.h"
#include "../Game.h"

Army::Army(Game* gamePtr): gamePtr(gamePtr)
{}

void Army::printFightingUnits()
{
	Unit* unit = nullptr;

	while (currentAttackers.dequeue(unit))
		unit->printFought();
}

void Army::logCurrentAttackers()
{
	if (currentAttackers.getCount() > 0)
	{
		gamePtr->log("Current attackers: [");
		for (int i = 0; i < currentAttackers.getCount(); i++)
		{
			Unit* unit = nullptr;
			currentAttackers.dequeue(unit);
			gamePtr->log(unit->toString() + ", fought units: [" + unit->foughtUnitToString() + "]");
			currentAttackers.enqueue(unit);
		}
		gamePtr->log("]");
	}
	else
	{
		gamePtr->log("Current attackers: []");
	}
}