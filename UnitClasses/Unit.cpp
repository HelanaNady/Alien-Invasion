#include <cmath>

#include "Unit.h"
#include "../Game.h"

int Unit::nextEarthId = 1;
int Unit::nextAlienId = 2000;

Unit::Unit(Game* gamePtr, UnitType unitType, double health, int power, int attackCapacity)
	: gamePtr(gamePtr), unitType(unitType), Ta(0), Td(0), power(power), attackCapacity(attackCapacity)
{
	setHealth(health);

	if (unitType == UnitType::ES || unitType == UnitType::EG || unitType == UnitType::ET || unitType == UnitType::EH)
	{
		id = nextEarthId++;
		armyType = ArmyType::EARTH;
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
	return Ta != 0;
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
	return Ta == 0 ? -1 : Ta - Tj;
}

int Unit::getDestructionDelay() const
{
	return Td == 0 ? -1 : Td - Ta;
}

int Unit::getBattleDelay() const
{
	return Td == 0 ? -1 : Td - Tj;
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