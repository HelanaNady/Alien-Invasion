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

	int N;
	int ESPercentage;
	int ETPercentage;
	int EGPercentage;
	int ASPercentage;
	int AMPercentage;
	int ADPercentage;
	int prob;
	Range earthPowerRange;
	Range earthHealthRange;
	Range earthAttackCapacityRange;
	Range alienPowerRange;
	Range alienHealthRange;
	Range alienAttackCapacityRange;

private:
	Unit* generateUnit(ArmyType) const; // Generate a unit of the given army type

public:
	RandomGenerator(Game*);
	void generateArmy(ArmyType) const; // Generate units for the given army type
	int getRandomNumber(int, int) const; // Generate a random number between the given range

	// Setters
	void setN(int);
	void setProb(int);

	void setEarthParameters(int, int, int, Range, Range, Range); // Sets earth parameters loaded by game class
	void setAlienParameters(int, int, int, Range, Range, Range); // Sets alien parameters loaded by game class
};

#endif