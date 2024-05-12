#ifndef UNIT_H
#define UNIT_H

#include <iostream>

#include "../DEFS.h"
#include "../Containers/LinkedQueue.h"

class Game;

class Unit
{
private:
	enum { MAX_EARTH_ID = 999, MAX_ALIEN_ID = 2999, MAX_EARTH_ALLIED_ID = 4999};

	static int nextEarthId;
	static int nextAlienId;
	static int nextEarthAlliedId;

	ArmyType armyType;
	UnitType unitType;

protected:
	Game* gamePtr;
	int id;

	int Tj; // Join time 
	int Ta; // First attack time
	int Td; // Destruction time

	double initialHealth; // Initial health
	double health; // Current health
	int power; // Attack power
	int attackCapacity; // Attack capacity

	LinkedQueue<int> foughtUnits; // A list of the units fought in the current timestep to be printed 

private:
	void setHealth(double); // Health setter with range check & initial health saving

public:
	Unit(Game*, UnitType, double, int, int);

	// Static functions
	static bool cantCreateEarthUnit(); // Check if the max number of earth units is reached
	static bool cantCreateAlienUnit(); // Check if the max number of alien units is reached
	static bool cantCreateEarthAlliedUnit(); // Check if the max number of allied units is reached 

	void receiveDamage(double); // Decrease the health of the unit by "UAP"

	double calcUAP(Unit*) const; // Calculates the damage caused when attacked by "attackerUnit"
	virtual bool attack() = 0;
	virtual void printFought() = 0;

	virtual bool needsHeal() const; // Check if the unit is eligible for healing
	bool isDead() const; // Check if the unit is dead
	bool hasBeenAttackedBefore() const; // Check if it has been attacked before

	void clearFoughtUnits(); // Clear the list of fought units

	// Getters
	int getId() const;
	ArmyType getArmyType() const;
	UnitType getUnitType() const;
	double getInitialHealth() const;
	double getHealth() const;
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

	// Print unit
	friend std::ostream& operator<<(std::ostream&, Unit*);
};

#endif