#ifndef DEFS_H
#define DEFS_H

enum GameMode
{
	INTERACTIVE,
	SILENT,
};

enum ArmyType
{
	EARTH, ALIEN, EARTH_ALLIED,
	ARMY_TOTAL,
};

enum UnitType
{
	ES, EG, ET, EH,
	AS, AD, AM,
	SU,
	UNIT_TOTAL,
};

struct Range
{
	int min;
	int max;
};

struct ArmyStatistics
{
	// Total Unit Counts
	int totalUnitsCount;

	// Total Destructed Unit Counts
	int totalDestructedUnitsCount;

	// Unit Delays
	int totalFirstAttackDelays;
	int totalBattleDelays;
	int totalDestructionDelays;
};

struct GameStatistics
{
	// Unit Counts
	int unitCounts[UnitType::UNIT_TOTAL];

	// Destructed Unit Counts
	int destructedUnitCounts[UnitType::UNIT_TOTAL];

	// Total infected Earth Soldiers
	int totalInfectedESCount;

	// Total Unit Counts
	int totalUnitsCount;

	// Total Destructed Unit Counts
	int totalDestructedUnitsCount;

	// Armies Statistics
	ArmyStatistics armyStatistics[ArmyType::ARMY_TOTAL];
};

#endif