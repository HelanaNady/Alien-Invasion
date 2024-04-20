#ifndef UNIT_H
#define UNIT_H

#include <iostream>

#include "../DEFS.h"

class Game;

class Unit
{
private:
	static int lastEarthId; // Last Earth unit ID used to generate the next ID
	static int lastAlienId; // Last Alien unit ID used to generate the next ID

	ArmyType armyType; // Army type
	UnitType unitType; // Unit type

protected:
	Game* gamePtr; // Pointer to the game object
	int id; // Unit ID

	int Tj; // Join time 
	int Ta; // First attack time
	int Td; // Destruction time

	int health; // Current health
	int power; // Attack power
	int attackCapacity; // Attack capacity

private:
	void setHealth(int); // Set the health of the unit used in the constructor

public:
	Unit(Game*, UnitType, int, int, int);

	void receiveDamage(int); // Receive damage from an attack
	int calcUAP(Unit*) const; // Calculates the damage caused when attacked by "attackerUnit"
	virtual void printFought() const = 0; // Print the unit
	virtual void attack() = 0; // Run the attack for the unit

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