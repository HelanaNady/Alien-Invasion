#include "Unit.h"
#include "../Game.h"
#include <cmath>

int Unit::lastEarthId = 0;
int Unit::lastAlienId = 1999;

Unit::Unit(Game* gamePtr, UnitType unitType, int health, int power, int attackCapacity)
	: gamePtr(gamePtr), unitType(unitType), Ta(-1), Td(0), Df(0), Dd(0), Db(0), health(health), power(power), attackCapacity(attackCapacity)
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

int Unit::getTjoin() const
{
	return Tj;
}

int Unit::getTattack() const
{
	return Ta;
}

int Unit::getTdestruction() const
{
	return Td;
}

int Unit::getDfirst() const
{
	return Df;
}

int Unit::getDdestruction() const
{
	return Dd;
}

int Unit::getDbattle() const
{
	return	Db;
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


void Unit::setTattack(int Ta)
{
	this->Ta = Ta;
}

void Unit::setTdestruction(int Td)
{
	this->Td = Td;
}

void Unit::setDfirst()
{
	Df = Ta - Tj; // First Attack Delay
}

void Unit::setDdestruction()
{
	Dd = Td - Ta; // Destruction Delay
}

void Unit::setDbattle()
{
	Db = Td - Tj; // Battle Time
}


std::ostream& operator<<(std::ostream& oStream, Unit* unitObj)
{
	oStream << unitObj->id;

	return oStream;
}
