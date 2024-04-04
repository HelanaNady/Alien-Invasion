#ifndef UNIT_H
#define UNIT_H

#include "../DEFS.h"

class Unit
{
private:
	static int lastEarthId;
	static int lastAlienId;

	UnitType unitType;
	int id;

	int Tj; // Join time 
	int Ta; // First attack time
	int Td; // Destruction time

	int Df; // First attack delay
	int Dd; // Destruction delay
	int Db; // Battle time

	int health; // Current health
	int power; // Attack power
	int attackCapacity; // Attack capacity
public:
	Unit(UnitType, int, int, int);

	void recieveDamage(int loss);
	virtual void print() = 0;
	virtual void attack(Unit*) = 0;  //shouldn't it be passed a list??? will check later
};
#endif