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

	ArmyType armyType; // Army type
	UnitType unitType; // Unit type
	int id; // Unit ID

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

	void receiveDamage(int); // Receive damage from an attack
	virtual void print() const = 0; // Print the unit
	virtual void attack(Unit*) = 0; // Run the attack for the unit

	bool isAlive() const; // Check if the unit is alive
	bool isDead() const; // Check if the unit is dead

	// Getters
	int getId() const;
	ArmyType getArmyType() const;
	UnitType getUnitType() const;
	int getHealth() const;
	int getPower() const;
	int getAttackCapacity() const;

	// Setters
	void setPower(int);
	void setAttackCapacity(int);

	friend std::ostream& operator<<(std::ostream&, Unit*);
};
#endif