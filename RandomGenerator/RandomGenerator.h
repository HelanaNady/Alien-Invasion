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

	// Counts needed for the outputfile statistics
	// Total units generated through the whole battle (all timesteps combined)
	int totalAScount;
	int totalAMcount;
	int totalADcount;
	int totalEScount;
	int totalETcount;
	int totalEGcount;

private:
	void loadParameters(std::string);
	Unit* generateUnit(ArmyType);

public:
	RandomGenerator(Game*, std::string);
	void generateArmy(ArmyType);
	int getRandomNumber(int, int) const;
	int getTotalUnitCount(UnitType) const;
};

#endif