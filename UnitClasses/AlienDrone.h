#ifndef ALIEN_DRONE_H
#define ALIEN_DRONE_H

#include "Unit.h"
class AlienDrone: public Unit
{
public:
	void print();
	void attack(Unit* aUnit);
};
#endif
