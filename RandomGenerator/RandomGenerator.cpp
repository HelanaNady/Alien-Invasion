#include "RandomGenerator.h"

RandomGenerator::RandomGenerator(int N, int ESPercentage, int ETPercentage, int EGPercentage, int ASPercentage, int AMPercentage, int ADPercentage, int prob, Range earthPowerRange, Range earthHealthRange, Range earthAttackCapacityRange, Range alienPowerRange, Range alienHealthRange, Range alienAttackCapacityRange)
{
    this->N = N;

	this->ESPercentage = ESPercentage;
	this->ETPercentage = ETPercentage;
	this->EGPercentage = EGPercentage;

	this->ASPercentage = ASPercentage;
	this->AMPercentage = AMPercentage;
	this->ADPercentage = ADPercentage;

	this->prob = prob;

	this->earthPowerRange = earthPowerRange;
	this->earthHealthRange = earthHealthRange;
	this->earthAttackCapacityRange = earthAttackCapacityRange;

	this->alienPowerRange = alienPowerRange;
	this->alienHealthRange = alienHealthRange;
	this->alienAttackCapacityRange = alienAttackCapacityRange;
}
