#include <iostream>
#include <fstream>

#include "Game.h"
#include "DEFS.h"
#include "UnitClasses/Unit.h"

Game::Game(): gameMode(GameMode::INTERACTIVE), currentTimestep(0), randomGenerator(this)
{}

void Game::run(GameMode gameMode, std::string inputFileName)
{
	// Change the game mode
	changeGameMode(gameMode);
	// Load parameters for the Random Generator
	loadParameters(inputFileName);

	// Run the game
	do
	{
		incrementTimestep();

		// Print the output
		if (gameMode == GameMode::INTERACTIVE)
			printAll();

		std::cout << "Press Enter to continue...";
		while (std::cin.get() != '\n');
	} while (!battleOver());
}

void Game::incrementTimestep()
{
	currentTimestep++;

	// Generate units for both armies
	randomGenerator.generateUnits();

	// Start the battle attack
	earthArmy.attack();
	alienArmy.attack();
}

void Game::changeGameMode(GameMode gameMode)
{
	this->gameMode = gameMode;
}

bool Game::battleOver()
{
	return currentTimestep >= 40 && (earthArmy.isDead() || alienArmy.isDead());
}

void Game::addUnit(Unit* unit)
{
	ArmyType armyType = unit->getArmyType();

	switch (armyType)
	{
		case ArmyType::EARTH:
			earthArmy.addUnit(unit);
			break;

		case ArmyType::ALIEN:
			alienArmy.addUnit(unit);
			break;
	}
}

LinkedQueue<Unit*> Game::getEnemyList(ArmyType armyType, UnitType unitType, int attackCapacity)
{
	LinkedQueue<Unit*> enemyUnits;
	Unit* enemyUnitPtr = nullptr;

	switch (armyType)
	{
		case ArmyType::EARTH:
			for (int i = 0; i < attackCapacity; i++)
			{
				enemyUnitPtr = earthArmy.removeUnit(unitType);
				if (enemyUnitPtr)
					enemyUnits.enqueue(enemyUnitPtr);
			}
			break;

		case ArmyType::ALIEN:
			for (int i = 0; i < attackCapacity; i++)
			{
				enemyUnitPtr = alienArmy.removeUnit(unitType);
				if (enemyUnitPtr)
					enemyUnits.enqueue(enemyUnitPtr);
			}
			break;
	}

	return enemyUnits;
}

void Game::addToKilledList(Unit* unit)
{
	killedList.enqueue(unit);
}

void Game::printAll()
{
	std::cout << "\nCurrent Timestep " << currentTimestep << std::endl;

	std::cout << "============== Earth Army Alive Units ==============" << std::endl;
	earthArmy.printArmy();

	std::cout << "============== Alien Army Alive Units ==============" << std::endl;
	alienArmy.printArmy();

	std::cout << "============== Units fighting at current step ==============" << std::endl;
	earthArmy.printFightingUnits();
	alienArmy.printFightingUnits();

	std::cout << "============== Killed/Destructed Units ==============" << std::endl;
	printKilledList();
}

void Game::printKilledList() const
{
	std::cout << killedList.getCount() << " units [";
	killedList.printList();
	std::cout << "]" << std::endl;
}

void Game::loadParameters(std::string fileName)
{
	std::fstream fin(fileName);
	std::string wholeFile;

	int N = 0;
	int ESPercentage = 0;
	int ETPercentage = 0;
	int EGPercentage = 0;
	int ASPercentage = 0;
	int AMPercentage = 0;
	int ADPercentage = 0;
	int prob = 0;
	Range earthPowerRange;
	Range earthHealthRange;
	Range earthAttackCapacityRange;
	Range alienPowerRange;
	Range alienHealthRange;
	Range alienAttackCapacityRange;

	if (fin.is_open())
	{
		fin >> N >> ESPercentage >> ETPercentage >> EGPercentage >> ASPercentage >> AMPercentage >> ADPercentage >> prob;

		char dummyHyphen;

		fin >> earthPowerRange.min >> dummyHyphen >> earthPowerRange.max;
		fin >> earthHealthRange.min >> dummyHyphen >> earthHealthRange.max;
		fin >> earthAttackCapacityRange.min >> dummyHyphen >> earthAttackCapacityRange.max;

		fin >> alienPowerRange.min >> dummyHyphen >> alienPowerRange.max;
		fin >> alienHealthRange.min >> dummyHyphen >> alienHealthRange.max;
		fin >> alienAttackCapacityRange.min >> dummyHyphen >> alienAttackCapacityRange.max;

		randomGenerator.setN(N);
		randomGenerator.setProb(prob);

		randomGenerator.setEarthParameters(ESPercentage, EGPercentage, ETPercentage, earthPowerRange, earthHealthRange, earthAttackCapacityRange);
		randomGenerator.setAlienParameters(ASPercentage, AMPercentage, ADPercentage, alienPowerRange, alienHealthRange, alienAttackCapacityRange);
	}
}

int Game::getCurrentTimestep() const
{
	return currentTimestep;
}

int Game::getUnitsCount(ArmyType armyType, UnitType unitType) const
{
	switch (armyType)
	{
		case (ArmyType::EARTH):
			return earthArmy.getUnitsCount(unitType);
		case (ArmyType::ALIEN):
			return alienArmy.getUnitsCount(unitType);
	}

	return 0;
}

Game::~Game()
{}