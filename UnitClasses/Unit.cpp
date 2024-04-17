#include "Unit.h"
#include "../Game.h"

int Unit::lastEarthId = 0;
int Unit::lastAlienId = 1999;

Unit::Unit(Game* gamePtr, UnitType unitType, int health, int power, int attackCapacity): gamePtr(gamePtr), unitType(unitType), Ta(0), Td(0), power(power), attackCapacity(attackCapacity)
{
	// Set the health of the unit
	setHealth(health);

	// Set the ID and the army type based on the unit type
	if (unitType == UnitType::ES || unitType == UnitType::EG || unitType == UnitType::ET) // Earth unit
	{
		id = ++lastEarthId; // Increment the last Earth unit ID
		armyType = ArmyType::EARTH;
	}
	else // Alien unit
	{
		id = ++lastAlienId; // Increment the last Alien unit ID
		armyType = ArmyType::ALIEN;
	}

	Tj = gamePtr->getCurrentTimestep(); // Set the join time to the current timestep
}

void Unit::setHealth(int health)
{
	// Check if the health value is within the range [1, 100]
	if (health < 1)
		health = 1;
	if (health > 100)
		health = 100;

	this->health = health;
}

void Unit::receiveDamage(int loss)
{
	health -= loss;

	if (health < 0)
		health = 0;
}

bool Unit::isAlive() const
{
	return health > 0;
}

bool Unit::isDead() const
{
	return !isAlive();
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

int Unit::getFirstAttackDelay() const
{
	return Ta - Tj;
}

int Unit::getDestructionDelay() const
{
	return Td - Ta;
}

int Unit::getBattleDelay() const
{
	return Td - Tj;
}

void Unit::setPower(int power)
{
	power = this->power;
}

void Unit::setAttackCapacity(int attackCapacity)
{
	attackCapacity = this->attackCapacity;
}

std::ostream& operator<<(std::ostream& oStream, Unit* unitObj)
{
	oStream << unitObj->id;

	return oStream;
}
