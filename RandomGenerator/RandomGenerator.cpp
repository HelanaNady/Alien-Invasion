#include "RandomGenerator.h"

#include <iostream>
#include <sstream>
#include <cstdlib>

#include "../UnitClasses/Unit.h"
#include "../UnitClasses/EarthSoldier.h"
#include "../UnitClasses/EarthGunnery.h"
#include "../UnitClasses/EarthTank.h"
#include "../UnitClasses/AlienSoldier.h"
#include "../UnitClasses/AlienMonster.h"
#include "../UnitClasses/AlienDrone.h"
#include "../Game.h"

RandomGenerator::RandomGenerator(Game* gamePtr, std::string wholeFile)
	: gamePtr(gamePtr), AScount(0), AMcount(0), ADcount(0), EScount(0), EGcount(0), ETcount(0)
{
	loadParameters(wholeFile);
}

void RandomGenerator::generateArmy(ArmyType armyType)
{
	int A = getRandomNumber(1, 100);

	if (A <= prob)
	{
		Unit* newUnit;

		for (int i = 0; i < N; i++)
		{
			newUnit = generateUnit(armyType);
			gamePtr->addUnit(newUnit);
		}
	}
}

void RandomGenerator::loadParameters(std::string wholeFile)
{
	std::stringstream ss(wholeFile);
	ss >> N >> ESPercentage >> ETPercentage >> EGPercentage >> ASPercentage >> AMPercentage >> ADPercentage >> prob;

	char dummyHyphen;

	ss >> earthPowerRange.min >> dummyHyphen >> earthPowerRange.max;
	ss >> earthHealthRange.min >> dummyHyphen >> earthHealthRange.max;
	ss >> earthAttackCapacityRange.min >> dummyHyphen >> earthAttackCapacityRange.max;

	ss >> alienPowerRange.min >> dummyHyphen >> alienPowerRange.max;
	ss >> alienHealthRange.min >> dummyHyphen >> alienHealthRange.max;
	ss >> alienAttackCapacityRange.min >> dummyHyphen >> alienAttackCapacityRange.max;
}

Unit* RandomGenerator::generateUnit(ArmyType armyType)
{
	Unit* newUnit = nullptr;

	int B = getRandomNumber(1, 100);

	if (armyType == ArmyType::EARTH)
	{
		int power = getRandomNumber(earthPowerRange.min, earthPowerRange.max);
		int health;
		if (earthHealthRange.max > 100) // Initial health shouldn't exceed 100
			health = getRandomNumber(earthHealthRange.min, 99);
		else
			health = getRandomNumber(earthHealthRange.min, earthHealthRange.max);
		int attackCapacity = getRandomNumber(earthAttackCapacityRange.min, earthAttackCapacityRange.max);

		if (B <= ESPercentage)
		{
			newUnit = new EarthSoldier(gamePtr, health, power, attackCapacity);
			EScount++;
		}
		else if (B <= (ESPercentage + ETPercentage))
		{
			newUnit = new EarthTank(gamePtr, health, power, attackCapacity);
			ETcount++;
		}
		else
		{
			newUnit = new EarthGunnery(gamePtr, health, power, attackCapacity);
			EGcount++;
		}
	}
	else
	{
		int power = getRandomNumber(alienPowerRange.min, alienPowerRange.max);
		int health;
		if (alienHealthRange.max > 100) // Initial health shouldn't exceed 100
			health = getRandomNumber(alienHealthRange.min, 99);
		else
			health = getRandomNumber(alienHealthRange.min, alienHealthRange.max);
		int attackCapacity = getRandomNumber(alienAttackCapacityRange.min, alienAttackCapacityRange.max);

		if (B <= ASPercentage)
			newUnit = new AlienSoldier(gamePtr, health, power, attackCapacity);
		else if (B <= (ASPercentage + AMPercentage))
			newUnit = new AlienMonster(gamePtr, health, power, attackCapacity);
		else
			newUnit = new AlienDrone(gamePtr, health, power, attackCapacity);
	}

	return newUnit;
}

int RandomGenerator::getRandomNumber(int min, int max) const
{
	return min + rand() % (max - min + 1);
}

int RandomGenerator::getTotalUnitCount(UnitType unitType) const
{
	switch (unitType)
	{
		case UnitType::AS:
			return AScount;
			break;
		case UnitType::AM:
			return AMcount;
			break;
		case UnitType::AD:
			return ADcount;
			break; 
		case UnitType::ES: 
			return EScount;
			break;
		case UnitType::ET: 
			return ETcount;
			break;
		case UnitType::EG: 
			return EGcount; 
			break;
	}
}
