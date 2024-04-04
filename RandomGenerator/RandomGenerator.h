#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include "../DEFS.h"
#include "../UnitClasses/Unit.h"

class RandomGenerator
{
private:
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

public:
	RandomGenerator(int, int, int, int, int, int, int, int, Range, Range, Range, Range, Range, Range);

	Unit* generateUnit();
	int getRandomNumber(int min, int max);
};

#endif