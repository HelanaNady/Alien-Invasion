#include <iostream>

#include "EarthAlliedArmy.h"
#include "../UnitClasses/Unit.h"
#include "../Game.h"

EarthAlliedArmy::EarthAlliedArmy(Game*): Army(gamePtr)
{}

void EarthAlliedArmy::addUnit(Unit* unit)
{
	savers.enqueue(unit);
}

Unit* EarthAlliedArmy::removeUnit(UnitType unitType)
{
	Unit* unit = nullptr;
	savers.dequeue(unit);
	return unit;
}

Unit* EarthAlliedArmy::pickAttacker(UnitType unitType)
{
	Unit* unit = nullptr;
	savers.peek(unit);
	return unit;
}

void EarthAlliedArmy::printArmy() const
{
	std::cout << savers.getCount() << " SU [";
	savers.printList();
	std::cout << "]" << std::endl;
}

bool EarthAlliedArmy::attack()
{
	bool didArmyAttack = false; // Flag to check if the army attacked
	
	// Make saver units attack 
	Unit* attacker = pickAttacker(UnitType::SU);

	if (attacker)
	{
		gamePtr->log("Attacking with SU: " + attacker->toString());
		bool didUnitAttack = attacker->attack();

		// Add the attacker to the current attackers queue
		if (didUnitAttack)
			currentAttackers.enqueue(attacker);

		// If any unit attacked, the army attacked
		didArmyAttack = didArmyAttack || didUnitAttack;
	}
	else
	{
		gamePtr->log("no su to attack with");
	}
	logCurrentAttackers();
	return didArmyAttack;
}

bool EarthAlliedArmy::isDead() const
{
	return savers.getCount();
}

int EarthAlliedArmy::getUnitsCount(UnitType) const
{
	return savers.getCount();
}

EarthAlliedArmy::~EarthAlliedArmy()
{
	Unit* unit = nullptr;
	while (savers.dequeue(unit))
	{
		delete unit;
		unit = nullptr;
	}
}

