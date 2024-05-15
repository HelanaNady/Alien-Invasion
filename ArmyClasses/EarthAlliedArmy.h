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

	void addUnit(Unit*);
	Unit* removeUnit(UnitType);
	virtual Unit* pickAttacker(UnitType);
	void printArmy() const;
	bool attack();
	bool isDead() const;

	// Getters
	int getUnitsCount(UnitType) const;
	~EarthAlliedArmy();
};

#endif