#include "Unit.h"

int Unit::lastEarthId = 0;
int Unit::lastAlienId = 0;

Unit::Unit(UnitType unitType, int health, int power, int attackCapacity): unitType(unitType), Tj(0), Ta(0), Td(0), Df(0), Dd(0), Db(0), health(health), power(power), attackCapacity(attackCapacity)
{
	if (unitType == UnitType::ES || unitType == UnitType::EG || unitType == UnitType::ET)
		id = ++lastEarthId;
	else
		id = ++lastAlienId;
}

void Unit::recieveDamage(int loss)
{
	health -= loss;
}