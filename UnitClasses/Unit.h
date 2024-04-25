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
	int UMLjoinTime; // Time when the unit joined the UML

	double initialHealth; // Initial health
	double health; // Current health
	int power; // Attack power
	int attackCapacity; // Attack capacity

	LinkedQueue<int> foughtUnits; // A list of the units fought in the current timestep to be printed 

private:
	void setHealth(double);

public:
	Unit(Game*, UnitType, double, int, int);

	void receiveDamage(double); // Decrease the health of the unit by "UAP"
	void receiveHeal(double); // Increase the health of the unit by "UHP"

	double calcUAP(Unit*) const; // Calculates the damage caused when attacked by "attackerUnit"
	virtual void attack() = 0; // Attack the enemy units
	virtual void printFought(); // Print the fought units

	bool isDead() const; // Check if the unit is dead
	bool needsHeal() const; // Check if the unit is eligible for healing
	bool isFirstAttack() const; // Check if it has been attacked before

	void clearFoughtUnits(); // Clear the list of fought units

	// Getters
	int getId() const;
	ArmyType getArmyType() const;
	UnitType getUnitType() const;
	int getInitialHealth() const;
	int getHealth() const;
	int getPower() const;
	int getAttackCapacity() const;
	int getUMLjoinTime() const;

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
	void setUMLjoinTime(int);

	// Time
	void setFirstTimeAttack(int);
	void setDestructionTime(int);

	// Print unit
	friend std::ostream& operator<<(std::ostream&, Unit*);
};

#endif