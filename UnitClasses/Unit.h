#ifndef UNIT_H
#define UNIT_H

#include <iostream>

#include "../DEFS.h"
#include "../Containers/LinkedQueue.h"

class Game;

class Unit
{
private:
	static int lastEarthId;
	static int lastAlienId;

	ArmyType armyType;
	UnitType unitType;

protected:
	Game* gamePtr;
	int id;

	int Tj; // Join time 
	int Ta; // First attack time
	int Td; // Destruction time

	int health; // Current health
	int power; // Attack power
	int attackCapacity; // Attack capacity

	LinkedQueue<int> foughtUnits; // A list of the units fought in the current timestep to be printed

private:
	void setHealth(int);

public:
	Unit(Game*, UnitType, int, int, int);

	void receiveDamage(int);
	int calcUAP(Unit*); // Calculates the damage caused when attacked by "attackerUnit"
	virtual void print() const = 0;
	virtual void attack() = 0;

	bool isAlive() const; // Check if the unit is alive
	bool isDead() const; // Check if the unit is dead
	bool isFirstAttack() const; // Check if it has been attacked before

	// Getters
	int getId() const;
	ArmyType getArmyType() const;
	UnitType getUnitType() const;
	int getHealth() const;
	int getPower() const;
	int getAttackCapacity() const;

	// Time
	int getJoinTime() const;
	int getFirstAttackTime() const;
	int getDestructionTime() const;

	// Delay
	int getFirstAttackDelay() const;
	int getDestructionDelay() const;
	int getBattleDelay() const;

	// Setters
	void setPower(int);
	void setAttackCapacity(int);

	// Time
	void setFirstTimeAttack(int);
	void setDestructionTime(int);

	friend std::ostream& operator<<(std::ostream&, Unit*);
};
#endif