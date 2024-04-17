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