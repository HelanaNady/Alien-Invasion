#ifndef ALLIED_ARMY_H
#define ALLIED_ARMY_H

#include "Army.h"
#include "../Containers/LinkedQueue.h"
#include "../UnitClasses/Unit.h"
#include "../UnitClasses/SaverUnit.h"

class AlliedArmy: public Army
{
private:
	LinkedQueue<Unit*> savers;
public:
	AlliedArmy(Game*);

	void addUnit(Unit*);
	Unit* removeUnit(UnitType);
	virtual Unit* pickAttacker(UnitType);
	void printArmy() const;
	bool attack();
	bool isDead() const;

	int getUnitsCount(UnitType) const;

	// Getters
};

#endif