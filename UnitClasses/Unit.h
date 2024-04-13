#ifndef UNIT_H
#define UNIT_H

#include <iostream>

#include "../DEFS.h"

class Game;

class Unit
{
private:
	Game* gamePtr; // Pointer to the game object

	static int lastEarthId; // Last Earth unit ID used to generate the next ID
	static int lastAlienId; // Last Alien unit ID used to generate the next ID

	int id; // Unit ID
	ArmyType armyType; // Army type
	UnitType unitType; // Unit type

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
	virtual void print() const = 0; // Print the unit
	virtual void attack() = 0; // Run the attack for the unit

	bool isAlive() const;
	bool isDead() const;

	// Getters
	int getId() const;
	ArmyType getArmyType() const;
	UnitType getUnitType() const;
	int getHealth() const;
	int getPower() const;
	int getAttackCapacity() const;
	int getFirstAttackDelay() const; // Get difference between first attack time and join time
	int getDestructionDelay() const; // Get difference between destruction time and first attack time
	int getBattleDelay() const; // Get difference between join time and destruction time

	// Setters
	void setPower(int);
	void setAttackCapacity(int);

	friend std::ostream& operator<<(std::ostream&, Unit*);
};

#endif