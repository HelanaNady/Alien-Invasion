#include <cmath>

#include "Unit.h"
#include "../Game.h"

int Unit::lastEarthId = 0;
int Unit::lastAlienId = 1999;

Unit::Unit(Game* gamePtr, UnitType unitType, double health, int power, int attackCapacity)
	: gamePtr(gamePtr), unitType(unitType), Ta(-1), Td(0), power(power), attackCapacity(attackCapacity)
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

int Unit::getInitialHealth() const
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

void Unit::receiveHeal(double UHP)
{
	health += UHP;
}

void Unit::clearFoughtUnits()
{
	int i = 0;
	while (foughtUnits.dequeue(i));
}

bool Unit::isDead() const
{
	return health <= 0;
}

bool Unit::needsHeal() const
{
	return ((unitType == UnitType::ES || unitType == UnitType::ET) && (health / initialHealth) <= 0.2);
}

bool Unit::isFirstAttack() const
{
	return Ta == -1;
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

int Unit::getUMLjoinTime() const
{
	return UMLjoinTime;
}

void Unit::setPower(int power)
{
	this->power = power;
}

void Unit::setUMLjoinTime(int UMLjoinTime)
{
	this->UMLjoinTime = UMLjoinTime;
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

std::string Unit::toString() const
{
	std::string unitTypeStr;
	switch (unitType)
	{
		case UnitType::ES:
			unitTypeStr = "Earth Soldier";
			break;
		case UnitType::ET:
			unitTypeStr = "Earth Tank";
			break;
		case UnitType::EG:
			unitTypeStr = "Earth Gunnery";
			break;
		case UnitType::EH:
			unitTypeStr = "Heal Unit";
			break;
		case UnitType::AS:
			unitTypeStr = "Alien Soldier";
			break;
		case UnitType::AM:
			unitTypeStr = "Alien Monster";
			break;
		case UnitType::AD:
			unitTypeStr = "Alien Drone";
			break;
	}

	return unitTypeStr + " (ID: " + std::to_string(id) + ", Health: " + std::to_string(health) + ", Power: " + std::to_string(power) + ", Attack Capacity: " + std::to_string(attackCapacity) + ")";
}

std::string Unit::foughtUnitToString()
{
	std::string foughtUnitsStr = "";

	int i = 0;
	for (int i = 0; i < foughtUnits.getCount(); i++)
	{
		int foughtUnitId;
		foughtUnits.dequeue(foughtUnitId);
		foughtUnitsStr += std::to_string(foughtUnitId) + ", ";
		foughtUnits.enqueue(foughtUnitId);
	}

	// Remove the last comma and space
	if (foughtUnitsStr.size() > 0)
		foughtUnitsStr = foughtUnitsStr.substr(0, foughtUnitsStr.size() - 2);

	return foughtUnitsStr;
}

std::string Unit::getUnitTypeString()
{
	return Unit::unitTypeString(unitType);
}

std::string Unit::unitTypeString(UnitType unitType)
{
	switch (unitType)
	{
		case UnitType::ES:
			return "ES";
		case UnitType::ET:
			return "ET";
		case UnitType::EG:
			return "EG";
		case UnitType::EH:
			return "EH";
		case UnitType::AS:
			return "AS";
		case UnitType::AM:
			return "AM";
		case UnitType::AD:
			return "AD";
	}
	return "";
}