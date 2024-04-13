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
	: gamePtr(gamePtr), totalAScount(0), totalAMcount(0), totalADcount(0), totalEScount(0), totalEGcount(0), totalETcount(0)
{
	loadParameters(wholeFile);
}

void RandomGenerator::generateArmy(ArmyType armyType)
{
	int A = getRandomNumber(1, 100);

	if (A <= prob)
	{
		Unit* newUnit = nullptr;

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
		int health = getRandomNumber(earthHealthRange.min, earthHealthRange.max);
		int attackCapacity = getRandomNumber(earthAttackCapacityRange.min, earthAttackCapacityRange.max);

		if (B <= ESPercentage)
		{
			newUnit = new EarthSoldier(gamePtr, health, power, attackCapacity);
			totalEScount++;
		}
		else if (B <= (ESPercentage + ETPercentage))
		{
			newUnit = new EarthTank(gamePtr, health, power, attackCapacity);
			totalETcount++;
		}
		else
		{
			newUnit = new EarthGunnery(gamePtr, health, power, attackCapacity);
			totalEGcount++;
		}
	}
	else
	{
		int power = getRandomNumber(alienPowerRange.min, alienPowerRange.max);
		int health = getRandomNumber(alienHealthRange.min, alienHealthRange.max);
		int attackCapacity = getRandomNumber(alienAttackCapacityRange.min, alienAttackCapacityRange.max);

		if (B <= ASPercentage)
		{
			newUnit = new AlienSoldier(gamePtr, health, power, attackCapacity);
			totalAScount++;
		}
		else if (B <= (ASPercentage + AMPercentage))
		{
			newUnit = new AlienMonster(gamePtr, health, power, attackCapacity);
			totalAMcount++;
		}
		else
		{
			newUnit = new AlienDrone(gamePtr, health, power, attackCapacity);
			totalADcount++;
		}
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
			return totalAScount;
		case UnitType::AM:
			return totalAMcount;
		case UnitType::AD:
			return totalADcount;
		case UnitType::ES:
			return totalEScount;
		case UnitType::ET:
			return totalETcount;
		case UnitType::EG:
			return totalEGcount;
	}
}
