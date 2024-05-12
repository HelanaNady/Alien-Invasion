#include <iostream>

#include "AlliedArmy.h"
#include "../UnitClasses/Unit.h"
#include "../Game.h"

AlliedArmy::AlliedArmy(Game*): Army(gamePtr)
{}

void AlliedArmy::addUnit(Unit* unit)
{
	savers.enqueue(unit);
}

Unit* AlliedArmy::removeUnit(UnitType unitType)
{
	Unit* unit = nullptr;
	if (unitType == UnitType::SU) // A check that I might remove later
		savers.dequeue(unit);
	return unit;
}

Unit* AlliedArmy::pickAttacker(UnitType unitType)
{
	Unit* unit = nullptr;
	savers.peek(unit);
	return unit;
}

void AlliedArmy::printArmy() const
{
	std::cout << savers.getCount() << " SU [";
	savers.printList();
	std::cout << "]" << std::endl;
}

bool AlliedArmy::attack()
{
	bool didArmyAttack = false; // Flag to check if the army attacked
	
	// Make saver units attack 
	Unit* attacker = pickAttacker(UnitType::SU);

	if (attacker)
	{
		bool didUnitAttack = attacker->attack();

		// Add the attacker to the current attackers queue
		if (didUnitAttack)
			currentAttackers.enqueue(attacker);

		// If any unit attacked, the army attacked
		didArmyAttack = didArmyAttack || didUnitAttack;
	}	
	return didArmyAttack;
}

bool AlliedArmy::isDead() const
{
	return savers.getCount();
}

// will be removed -> no point 
int AlliedArmy::getUnitsCount(UnitType) const
{
	return savers.getCount();
}

AlliedArmy::~AlliedArmy()
{
	Unit* unit = nullptr;
	while (savers.dequeue(unit))
	{
		delete unit;
		unit = nullptr;
	}
}

