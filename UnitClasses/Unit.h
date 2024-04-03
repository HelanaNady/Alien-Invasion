#ifndef UNIT_H
#define UNIT_H

enum UnitType
{
	ES, EG, ET,
	AS, AD, AM
};
class Unit
{
	UnitType unitType;
	int id;

	int Tj; // Join time 
	int Ta; // First attack time
	int Td; // Destruction time

	int Df; // First attack delay
	int Dd; // Destruction delay
	int Db; // Battle time

	int health;
	int power;
	int attackCapacity;
public:
	void recieveDamage(int loss);
	virtual void print() = 0;
	virtual void attack(Unit* aUnit) = 0;  //shouldn't it be passed a list??? will check later

};
#endif