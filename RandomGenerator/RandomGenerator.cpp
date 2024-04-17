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

RandomGenerator::RandomGenerator(Game* gamePtr):gamePtr(gamePtr)
{
}

void RandomGenerator::generateArmy(ArmyType armyType) const
{
	int A = getRandomNumber(1, 100);

	if (A <= prob) // If the probability is satisfied, generate the units
	{
		Unit* newUnit = nullptr;

		// Generate N units
		for (int i = 0; i < N; i++)
		{
			newUnit = generateUnit(armyType);
			gamePtr->addUnit(newUnit); // Add the unit to the suitable army & list based on the unit type
		}
	}
}


Unit* RandomGenerator::generateUnit(ArmyType armyType) const
{
	Unit* newUnit = nullptr;

	int B = getRandomNumber(1, 100);

	if (armyType == ArmyType::EARTH)
	{
		int power = getRandomNumber(earthPowerRange.min, earthPowerRange.max); // Generate a random power value
		int health = getRandomNumber(earthHealthRange.min, earthHealthRange.max); // Generate a random health value
		int attackCapacity = getRandomNumber(earthAttackCapacityRange.min, earthAttackCapacityRange.max); // Generate a random attack capacity value

		// Generate a random unit based on the B value and the percentages
		if (B <= ESPercentage)
			newUnit = new EarthSoldier(gamePtr, health, power, attackCapacity);
		else if (B <= (ESPercentage + ETPercentage))
			newUnit = new EarthTank(gamePtr, health, power, attackCapacity);
		else
			newUnit = new EarthGunnery(gamePtr, health, power, attackCapacity);
	}
	else
	{
		int power = getRandomNumber(alienPowerRange.min, alienPowerRange.max); // Generate a random power value
		int health = getRandomNumber(alienHealthRange.min, alienHealthRange.max); // Generate a random health value
		int attackCapacity = getRandomNumber(alienAttackCapacityRange.min, alienAttackCapacityRange.max); // Generate a random attack capacity value

		// Generate a random unit based on the B value and the percentages
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

void RandomGenerator::setESPercentage(int ESPercentage)
{
	 this->ESPercentage = ESPercentage;
}

void RandomGenerator::setETPercentage(int ETPercentage)
{
	this->ETPercentage = ETPercentage;
}

void RandomGenerator::setEGPercentage(int EGPercentage)
{
	this->EGPercentage = EGPercentage;
}

void RandomGenerator::setASPercentage(int ASPercentage)
{
	this->ASPercentage = ASPercentage;
}

void RandomGenerator::setAMPercentage(int AMPercentage)
{
	this->AMPercentage = AMPercentage;
}

void RandomGenerator::setADPercentage(int ADPercentage)
{
	this->ADPercentage = ADPercentage;
}

void RandomGenerator::setProb(int prob)
{
	this->prob = prob;
}

void RandomGenerator::setEarthPowerRange(Range earthPowerRange)
{
	this->earthPowerRange = earthPowerRange;
}

void RandomGenerator::setEarthHealthRange(Range earthHealthRange)
{
	this->earthPowerRange = earthHealthRange;
}

void RandomGenerator::setEarthAttackCapacityRange(Range earthAtackCapacityRange)
{
	this->earthAttackCapacityRange = earthAttackCapacityRange;
}

void RandomGenerator::setAlienPowerRange(Range alienPowerRange)
{
	this->alienPowerRange = alienPowerRange;
}

void RandomGenerator::setAlienHealthRange(Range alienHealthRange)
{
	this->alienHealthRange = alienHealthRange;
}

void RandomGenerator::setAlienAttackCapacityRange(Range alienAttackCapacityRange)
{
	this->alienAttackCapacityRange = alienAttackCapacityRange;
}
