#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H

#include "Unit.h"
#include "../DEFS.h" 

class AlienMonster: public Unit
{
public:
	AlienMonster(UnitType, int, int, int); 
	void print();
	void attack(Unit* aUnit);
};
#endif
