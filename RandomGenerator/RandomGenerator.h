#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <string>

#include "../DEFS.h"
#include "../UnitClasses/Unit.h"

class Game;

class RandomGenerator
{
private:
	Game* gamePtr;

	int N; // Number of units to generate
	int ESPercentage; // Earth Soldier percentage
	int ETPercentage; // Earth Tank percentage
	int EGPercentage; // Earth Gunner percentage
	int ASPercentage; // Alien Soldier percentage
	int AMPercentage; // Alien Monster percentage
	int ADPercentage; // Alien Drone percentage
	int prob; // Probability of generating the units
	Range earthPowerRange; // Earth unit power range
	Range earthHealthRange; // Earth unit health range
	Range earthAttackCapacityRange; // Earth unit attack capacity range
	Range alienPowerRange; // Alien unit power range
	Range alienHealthRange; // Alien unit health range
	Range alienAttackCapacityRange; // Alien unit attack capacity range

private:
	Unit* generateUnit(ArmyType) const; // Generate a unit of the given army type

public:
	RandomGenerator(Game*);
	void generateArmy(ArmyType) const; // Generate units for the given army type
	int getRandomNumber(int, int) const; // Generate a random number between the given range

	// Setters
	void setN(int);
	void setESPercentage(int);
	void setETPercentage(int);
	void setEGPercentage(int);

	void setASPercentage(int);
	void setAMPercentage(int);
	void setADPercentage(int);

	void setProb(int);

	void setEarthPowerRange(Range);
	void setEarthHealthRange(Range);
	void setEarthAttackCapacityRange(Range);

	void setAlienPowerRange(Range);
	void setAlienHealthRange(Range);
	void setAlienAttackCapacityRange(Range);
};

#endif