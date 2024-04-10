#ifndef UNIT_H
#define UNIT_H

#include <iostream>

#include "../DEFS.h"
#include "../Containers/LinkedQueue.h"

class Game;

class Unit
{
private:
	Game* gamePtr;

	static int lastEarthId;
	static int lastAlienId;

	ArmyType armyType;
	UnitType unitType;
protected:
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

	LinkedQueue<int> foughtUnits; // A list of the units fought in the current timestep to be printed

public:
	Unit(Game*, UnitType, int, int, int);

	void recieveDamage(int);
	int calcUAP(Unit*); // Calculates the damage caused when attacked by "attackerUnit"
	virtual void print() const = 0;
	virtual void attack(Unit*) = 0;

	// Getters
	int getId() const;
	ArmyType getArmyType() const;
	UnitType getUnitType() const;
	int getHealth() const;
	int getPower() const;
	int getAttackCapacity() const;
	// Time
	int getTjoin() const;
	int getTattack() const;
	int getTdestruction() const;
	// Delay
	int getDfirst() const;
	int getDdestruction() const;
	int getDbattle() const;
	
	
	// Setters
	void setHealth(int);
	void setPower(int);
	void setAttackCapacity(int);
	// Time
	void setTattack(int);
	void setTdestruction(int);
	//Delay
	void setDfirst();
	void setDdestruction();
	void setDbattle();

	friend std::ostream& operator<<(std::ostream&, Unit*);
};
#endif