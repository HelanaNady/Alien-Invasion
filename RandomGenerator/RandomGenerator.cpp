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

RandomGenerator::RandomGenerator(Game* gamePtr): gamePtr(gamePtr)
{
	// Initialize the parameters with default values
	setN(0);
	setProb(0);
	setEarthParameters(0, 0, 0, { 0, 0 }, { 0, 0 }, { 0, 0 });
	setAlienParameters(0, 0, 0, { 0, 0 }, { 0, 0 }, { 0, 0 });
}

void RandomGenerator::generateArmy(ArmyType armyType) const
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

Unit* RandomGenerator::generateUnit(ArmyType armyType) const
{
	Unit* newUnit = nullptr;

	int B = getRandomNumber(1, 100);

	if (armyType == ArmyType::EARTH)
	{
		int power = getRandomNumber(earthPowerRange.min, earthPowerRange.max);
		int health = getRandomNumber(earthHealthRange.min, earthHealthRange.max);
		int attackCapacity = getRandomNumber(earthAttackCapacityRange.min, earthAttackCapacityRange.max);

		if (B <= ESPercentage)
			newUnit = new EarthSoldier(gamePtr, health, power, attackCapacity);
		else if (B <= (ESPercentage + ETPercentage))
			newUnit = new EarthTank(gamePtr, health, power, attackCapacity);
		else
			newUnit = new EarthGunnery(gamePtr, health, power, attackCapacity);
	}
	else
	{
		int power = getRandomNumber(alienPowerRange.min, alienPowerRange.max);
		int health = getRandomNumber(alienHealthRange.min, alienHealthRange.max);
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

void RandomGenerator::setN(int N)
{
	this->N = N;
}

void RandomGenerator::setProb(int prob)
{
	this->prob = prob;
}

void RandomGenerator::setEarthParameters(int ESPercentage, int ETPercentage, int EGPercentage, Range earthPowerRange, Range earthHealthRange, Range earthAttackCapacityRange)
{
	this->ESPercentage = ESPercentage;
	this->ETPercentage = ETPercentage;
	this->EGPercentage = EGPercentage;

	this->earthPowerRange = earthPowerRange;
	this->earthPowerRange = earthHealthRange;
	this->earthAttackCapacityRange = earthAttackCapacityRange;
}

void RandomGenerator::setAlienParameters(int ASPercentage, int AMPercentage, int ADPercentage, Range alienPowerRange, Range alienHealthRange, Range alienAttackCapacityRange)
{
	this->ASPercentage = ASPercentage;
	this->AMPercentage = AMPercentage;
	this->ADPercentage = ADPercentage;

	this->alienPowerRange = alienPowerRange;
	this->alienPowerRange = alienHealthRange;
	this->alienAttackCapacityRange = alienAttackCapacityRange;
}

