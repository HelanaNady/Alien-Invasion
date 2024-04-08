#ifndef DEFS_H
#define DEFS_H

enum GameMode
{
	INTERACTIVE,
	SILENT,
};

struct Range
{
	int min;
	int max;
};

enum ArmyType
{
	EARTH, ALIEN
};

enum UnitType
{
	ES, EG, ET,
	AS, AD, AM
};

#endif