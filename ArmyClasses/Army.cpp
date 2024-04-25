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