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
	return Df;
}

int Unit::getDestructionDelay() const
{
	return Dd;
}

int Unit::getBattleDelay() const
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

void Unit::setFirstTimeAttack(int Ta)
{
	this->Ta = Ta;
}

void Unit::setDestructionTime(int Td)
{
	this->Td = Td;
}

void Unit::setFirstAttackDelay()
{
	Df = Ta - Tj; // First Attack Delay
}

void Unit::setDestructionDelay()
{
	Dd = Td - Ta; // Destruction Delay
}

void Unit::setBattleDelay()
{
	Db = Td - Tj; // Battle Time
}

std::ostream& operator<<(std::ostream& oStream, Unit* unitObj)
{
	oStream << unitObj->id;

	return oStream;
}
