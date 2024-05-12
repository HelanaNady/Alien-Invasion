#include <cmath>

#include "Unit.h"
#include "../Game.h"

int Unit::nextEarthId = 1;
int Unit::nextAlienId = 2000;
int Unit::nextEarthAlliedId = 4000;

Unit::Unit(Game* gamePtr, UnitType unitType, double health, int power, int attackCapacity)
	: gamePtr(gamePtr), unitType(unitType), Ta(-1), Td(-1), power(power), attackCapacity(attackCapacity)
{
	setHealth(health);

	if (unitType == UnitType::ES || unitType == UnitType::EG || unitType == UnitType::ET || unitType == UnitType::EH)
	{
		id = nextEarthId++;
		armyType = ArmyType::EARTH;
	}
	else if (unitType == UnitType::SU)
	{
		id = nextEarthAlliedId++;
		armyType = ArmyType::EARTH_ALLIED;
	}
	else 
	{
		id = nextAlienId++;
		armyType = ArmyType::ALIEN;
	}

	// set the unit's join time
	Tj = gamePtr->getCurrentTimestep();
}

bool Unit::cantCreateEarthUnit()
{
	return nextEarthId > MAX_EARTH_ID;
}

bool Unit::cantCreateAlienUnit()
{
	return nextAlienId > MAX_ALIEN_ID;
}

bool Unit::cantCreateEarthAlliedUnit()
{
	return nextEarthAlliedId > MAX_EARTH_ALLIED_ID;
}

void Unit::setHealth(double health)
{
	// Check if the health value is within the range [1, 100]
	if (health < 1)
		health = 1;
	if (health > 100)
		health = 100;

	this->initialHealth = health; // Save the initial health value for healing purposes
	this->health = health;
}

double Unit::getInitialHealth() const
{
	return initialHealth;
}

void Unit::receiveDamage(double UAP)
{
	// Decrement the unit's health, force it to its minimum value if it exceeded it
	health = health - UAP > 0 ? health - UAP : 0;

	// Check if it's the unit's first time being attacked and set it if needed
	if (!hasBeenAttackedBefore())
		Ta = gamePtr->getCurrentTimestep();
}

void Unit::clearFoughtUnits()
{
	int i = 0;
	while (foughtUnits.dequeue(i));
}

bool Unit::needsHeal() const
{
	return false;
}

bool Unit::isDead() const
{
	return health <= 0;
}

bool Unit::hasBeenAttackedBefore() const
{
	return Ta != -1;
}

double Unit::calcUAP(Unit* attackedUnit) const
{
	return (power * health / 100) / sqrt(attackedUnit->health);
}

int Unit::getId() const
{
	return id;
}

UnitType Unit::getUnitType() const
{
	return unitType;
}

ArmyType Unit::getArmyType() const
{
	return armyType;
}

double Unit::getHealth() const
{
	return health;
}

int Unit::getPower() const
{
	return power;
}

int Unit::getAttackCapacity() const
{
	return attackCapacity;
}

int Unit::getJoinTime() const
{
	return Tj;
}

int Unit::getFirstAttackTime() const
{
	return Ta;
}

int Unit::getDestructionTime() const
{
	return Td;
}

int Unit::getFirstAttackDelay() const
{
	return hasBeenAttackedBefore() ? Ta - Tj : -1;
}

int Unit::getDestructionDelay() const
{
	return isDead() ? Td - Ta : -1;
}

int Unit::getBattleDelay() const
{
	return isDead() ? Td - Tj : -1;
}

void Unit::setPower(int power)
{
	this->power = power;
}

void Unit::setAttackCapacity(int attackCapacity)
{
	this->attackCapacity = attackCapacity;
}

void Unit::setFirstTimeAttack(int Ta)
{
	this->Ta = Ta;
}

void Unit::setDestructionTime(int Td)
{
	this->Td = Td;
}

std::ostream& operator<<(std::ostream& oStream, Unit* unitObj)
{
	oStream << unitObj->id;
	EarthSoldier* ESunit = dynamic_cast<EarthSoldier*>(unitObj);
	if (ESunit && ESunit->isInfected())
	{
		oStream << "*";
	}
	return oStream;
}