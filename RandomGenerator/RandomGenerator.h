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
	void loadParameters(std::string);
	Unit* generateUnit(ArmyType) const;

public:
	RandomGenerator(Game*, std::string);
	void generateArmies() const;
	int getRandomNumber(int, int) const;
};

#endif