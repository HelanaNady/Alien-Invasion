#include "Unit.h"
#include "../Game.h"
#include <cmath>

int Unit::lastEarthId = 0;
int Unit::lastAlienId = 1999;

Unit::Unit(Game* gamePtr, UnitType unitType, int health, int power, int attackCapacity): gamePtr(gamePtr), unitType(unitType), Ta(0), Td(0), Df(0), Dd(0), Db(0), health(health), power(power), attackCapacity(attackCapacity)
{
	if (unitType == UnitType::ES || unitType == UnitType::EG || unitType == UnitType::ET)
	{
		id = ++lastEarthId;
		armyType = ArmyType::EARTH;
	}
	else
	{
		id = ++lastAlienId;
		armyType = ArmyType::ALIEN;
	}

	Tj = gamePtr->getCurrentTimestep();
}

void Unit::recieveDamage(int UAP)
{
	health -= UAP;

	if (health < 0)
		health = 0;
}

int Unit::calcUAP(Unit* attackedUnit)
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

int Unit::getHealth() const
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

int Unit::getDelay(char c) const
{
	switch (c)
	{
		case 'f': // First Attack Delay
			return Df;
			break;
		case 'd':  // Destruction Delay
			return Dd;
			break;
		case 'b':
			return Db; // Battle Time
			break;
	}
}

int Unit::getTime(char c) const
{
	switch(c)
	{
		case 'j': // Join Time
			return Tj;
			break;
		case 'a':  // First Attack Time
			return Ta;
			break;
		case 'd':
			return Td; // Destruction Time
			break;
	}
}

void Unit::setHealth(int health)
{
	health = this->health;
}

void Unit::setPower(int power)
{
	power = this->power;
}

void Unit::setAttackCapacity(int attackCapacity)
{
	attackCapacity = this->attackCapacity;
}

void Unit::setDelay(char c)
{
	switch (c)
	{
		case 'f': // First Attack Delay
			Df = Ta - Tj; 
			break;
		case 'd':  // Destruction Delay
			Dd = Td - Ta;
			break;
		case 'b':
			Db = Td - Tj; // Battle Time
			break;
	}
}

std::ostream& operator<<(std::ostream& oStream, Unit* unitObj)
{
	oStream << unitObj->id;

	return oStream;
}
