#ifndef EARTH_ALLIED_ARMY_H
#define EARTH_ALLIED_ARMY_H

#include "Army.h"
#include "../Containers/LinkedQueue.h"
#include "../UnitClasses/Unit.h"
#include "../UnitClasses/SaverUnit.h"

class EarthAlliedArmy: public Army
{
private:
	LinkedQueue<Unit*> savers;

public:
	EarthAlliedArmy(Game*);

	void addUnit(Unit*); // Add a unit to the army
	Unit* removeUnit(UnitType); // Remove a unit from the army and return it
	Unit* pickAttacker(UnitType); // Pick an attacker from the army and return it

	bool attack(); // Attack the enemy army
	bool isDead() const; // Check if the army is dead

	void printArmy() const; // Print the army units

	// Getters
	int getUnitsCount(UnitType) const; // Get the count of a specific unit type

	~EarthAlliedArmy();
};

#endif