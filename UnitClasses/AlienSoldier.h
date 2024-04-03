#ifndef ALIEN_SOLDIER_H
#define ALIEN_SOLDIER_H

#include "Unit.h"
class AlienSoldier : public Unit
{
public:
	void print();
	void attack(Unit* aUnit);
};
#endif
