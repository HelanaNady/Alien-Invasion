#ifndef DEFS_H
#define DEFS_H

enum GameMode
{
	INTERACTIVE,
	SILENT,
};

enum ArmyType
{
	EARTH, ALIEN
};

enum UnitType
{
	ES, EG, ET, EH,
	AS, AD, AM,
	UNIT_TOTAL,
};

struct Range
{
	int min;
	int max;
};

struct GameStatistics
{
	// Unit Counts
	int unitCounts[UnitType::UNIT_TOTAL];

	// Total Unit Counts
	int totalEarthUnitsCount;
	int totalAlienUnitsCount;

	// Destructed Unit Counts
	int destructedUnitCounts[UnitType::UNIT_TOTAL];
	int totalDestructedUnitsCount;

	// Unit Delays
	int totalEarthFirstAttackDelays;
	int totalEarthBattleDelays;
	int totalEarthDestructionDelays;

	int totalAlienFirstAttackDelays;
	int totalAlienBattleDelays;
	int totalAlienDestructionDelays;
};
#endif