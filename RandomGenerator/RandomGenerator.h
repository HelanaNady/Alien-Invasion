#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include "../DEFS.h"
#include "../UnitClasses/Unit.h"

class Game;

class RandomGenerator
{
private:
	Game* gamePtr;
	bool isGeneratingSavers;

	int N;
	int ESPercentage;
	int ETPercentage;
	int EGPercentage;
	int ASPercentage;
	int AMPercentage;
	int ADPercentage;
	int EHPercentage;
	int prob;

	Range earthPowerRange;
	Range earthHealthRange;
	Range earthAttackCapacityRange;
	Range alienPowerRange;
	Range alienHealthRange;
	Range alienAttackCapacityRange;
	Range earthAlliedPowerRange;
	Range earthAlliedHealthRange;
	Range earthAlliedAttackCapacityRange;

private:
	Unit* generateUnit(ArmyType); // Generate a unit of the given army type
	bool willGenerateSavers(); // A check to determine the need of generating savers

public:
	RandomGenerator(Game*);
	void generateUnits(); // Generate units for the both armies
	int getRandomNumber(int, int) const; // Generate a random number between the given range

	// Setters
	void setN(int);
	void setProb(int);

	void setEarthParameters(int, int, int, int, Range, Range, Range); // Sets earth parameters loaded by game class
	void setAlienParameters(int, int, int, Range, Range, Range); // Sets alien parameters loaded by game class
	void setEarthAlliedParameters(Range, Range, Range); // Sets allied parameters loaded by game class
};

#endif