#include <iostream>

#include "EarthAlliedArmy.h"
#include "../UnitClasses/Unit.h"
#include "../Game.h"

EarthAlliedArmy::EarthAlliedArmy(Game* gamePtr): Army(gamePtr)
{}

void EarthAlliedArmy::killSaverUnits()
{
	Unit* unit = nullptr;
	while (savers.dequeue(unit))
	{
		unit->receiveDamage(unit->getHealth()); // Make unit health 0
		gamePtr->addToKilledList(unit); // Add unit to killed list

		unit = nullptr;
	}
}

void EarthAlliedArmy::addUnit(Unit* unit)
{
	UnitType unitType = unit->getUnitType();

	switch (unitType)
	{
		case UnitType::SU:
			savers.enqueue(unit);
			break;
	}
}

Unit* EarthAlliedArmy::removeUnit(UnitType unitType)
{
	Unit* unit = nullptr;

	switch (unitType)
	{
		case UnitType::SU:
			savers.dequeue(unit);
			break;
	}

	return unit;
}

Unit* EarthAlliedArmy::pickAttacker(UnitType unitType)
{
	Unit* unit = nullptr;

	switch (unitType)
	{
		case UnitType::SU:
			savers.peek(unit);
			break;
	}

	return unit;
}

bool EarthAlliedArmy::attack()
{
	// If there are no infected units, saver units should be killed
	if (gamePtr->getInfectedUnitsCount() == 0)
	{
		killSaverUnits();
		return false;
	}

	// Flag to check if the army attacked
	bool didArmyAttack = false;

	// Pick an attacker from the army to attack
	Unit* attacker = pickAttacker(UnitType::SU);

	if (attacker)
	{
		// Attack the enemy
		bool didUnitAttack = attacker->attack();

		// Add the attacker to the current attackers queue
		if (didUnitAttack)
			currentAttackers.enqueue(attacker);

		// If any unit attacked, the army attacked
		didArmyAttack = didArmyAttack || didUnitAttack;
	}

	return didArmyAttack; // Return whether the army attacked
}

bool EarthAlliedArmy::isDead() const
{
	return savers.getCount() == 0;
}

void EarthAlliedArmy::printArmy() const
{
	std::cout << savers.getCount() << " SU [";
	savers.printList();
	std::cout << "]" << std::endl;
}

int EarthAlliedArmy::getUnitsCount(UnitType unitType) const
{
	switch (unitType)
	{
		case UnitType::SU:
			return savers.getCount();
	}

	return 0;
}

EarthAlliedArmy::~EarthAlliedArmy()
{
	// Delete all units in the army
	Unit* unit = nullptr;
	while (savers.dequeue(unit))
	{
		delete unit;
		unit = nullptr;
	}
}

