#ifndef ALIEN_MONSTER_H
#define ALIEN_MONSTER_H

#include "Unit.h"
class AlienMonster: public Unit
{
public:
	void print();
	void attack(Unit* aUnit);
};
#endif
