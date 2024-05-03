#include <cmath>

#include "Unit.h"
#include "../Game.h"

int Unit::lastEarthId = 0;
int Unit::lastAlienId = 1999;

Unit::Unit(Game* gamePtr, UnitType unitType, double health, int power, int attackCapacity)
	: gamePtr(gamePtr), unitType(unitType), Ta(0), Td(0), power(power), attackCapacity(attackCapacity)
{
	setHealth(health);

	if (unitType == UnitType::ES || unitType == UnitType::EG || unitType == UnitType::ET || unitType == UnitType::EH)
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
	health -= UAP;

	if (health <= 0)
	{
		health = 0;
		Td = gamePtr->getCurrentTimestep(); // Set the destruction time
	}
}

void Unit::clearFoughtUnits()
{
	int i = 0;
	while (foughtUnits.dequeue(i));
}

bool Unit::needsHeal()
{
	return dynamic_cast<HealableUnit*>(this) && (health / initialHealth) <= 0.2;
}

bool Unit::isDead() const
{
	return health <= 0;
}

bool Unit::isFirstAttack() const
{
	return Ta == 0;
}

double Unit::calcUAP(Unit* attackedUnit) const
{
	return (power * health / 100) / sqrt(attackedUnit->health);
}

void Unit::printFought()
{}

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
	return Ta == 0 ? 0 : Ta - Tj;
}

int Unit::getDestructionDelay() const
{
	return Td == 0 ? 0 : Td - Ta;
}

int Unit::getBattleDelay() const
{
	return Td == 0 ? 0 : Td - Tj;
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

	return oStream;
}