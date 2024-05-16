#include "Army.h"
#include "../Game.h"

Army::Army(Game* gamePtr): gamePtr(gamePtr)
{}


int Army::getFightingUnitsCount() const
{
	return currentAttackers.getCount();
}
