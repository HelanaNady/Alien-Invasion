#include <iostream>
#include <fstream>

#include "Game.h"
#include "DEFS.h"
#include "UnitClasses/Unit.h"

Game::Game(): gameMode(GameMode::INTERACTIVE), currentTimestep(0), randomGenerator(nullptr)
{}

void Game::run(GameMode gameMode, std::string inputFileName)
{
	// Change the game mode
	changeGameMode(gameMode);

	// Load parameters for random generator
	std::string inputParameters = loadFromFile(inputFileName);
	randomGenerator = new RandomGenerator(this, inputParameters);

	// Run the game
	while (!battleOver())
	{
		incrementTimestep();
	}
	//printOutputFile();
}

void Game::incrementTimestep()
{
	currentTimestep++;

	// Generate units for both armies
	randomGenerator->generateArmy(ArmyType::EARTH);
	randomGenerator->generateArmy(ArmyType::ALIEN);

	if (gameMode == GameMode::INTERACTIVE)
		printAll();
}

void Game::changeGameMode(GameMode gameMode)
{
	this->gameMode = gameMode;
}

bool Game::battleOver()
{
	return currentTimestep > 40 && !(earthArmy.isDead() && alienArmy.isDead());
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


void Game::killUnit(Unit* unit)
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
	earthArmy.printFightingUnits(); // Is this right?
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

std::string Game::loadFromFile(std::string fileName)
{
	std::fstream fin(fileName);
	std::string wholeFile;

	if (fin.is_open())
	{
		std::string newLine;
		while (std::getline(fin, newLine))
			wholeFile += newLine + " ";
	}

	return wholeFile;
}

int Game::getCurrentTimestep() const
{
	return currentTimestep;
}

Game::~Game()
{
	// Delete the random generator
	if (randomGenerator != nullptr)
		delete randomGenerator;
}