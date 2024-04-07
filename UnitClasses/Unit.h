#ifndef UNIT_H
#define UNIT_H

#include <iostream>

#include "../DEFS.h"

class Game;

class Unit
{
private:
	Game* gamePtr;

	static int lastEarthId;
	static int lastAlienId;

	ArmyType armyType;
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
	Unit(Game*, UnitType, int, int, int);

	void recieveDamage(int);
	virtual void print() const = 0;
	virtual void attack(Unit*) = 0;

	// Getters
	int getId() const;
	ArmyType getArmyType() const;
	UnitType getUnitType() const;
	int getHealth() const;
	int getPower() const;
	int getAttackCapacity() const;
	void setHealth(int);
	void setPower(int);
	void setAttackCapacity(int);

	friend std::ostream& operator<<(std::ostream&, Unit*);
};
#endif