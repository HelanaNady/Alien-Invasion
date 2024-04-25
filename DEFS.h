#ifndef DEFS_H
#define DEFS_H

struct Range
{
	int min;
	int max;
};

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
	AS, AD, AM
};

#endif