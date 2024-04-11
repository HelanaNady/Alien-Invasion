#include <iostream>
#include <fstream>

#include "Game.h"
#include "DEFS.h"
#include "UnitClasses/Unit.h"
#include "FileHandler/FileHandler.h"

Game::Game(): gameMode(GameMode::INTERACTIVE), currentTimestep(0), randomGenerator(nullptr)
{}

void Game::run(GameMode gameMode, std::string inputFileName)
{
	// Change the game mode
	changeGameMode(gameMode);

	// Load parameters for random generator
	std::string inputParameters = FileHandler::loadFile(inputFileName);
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
		case (ArmyType::EARTH):
			earthArmy.addUnit(unit);
			break;
		default:
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
		case(ArmyType::EARTH):
			for (int i = 0; i < attackCapacity; i++)
			{
				enemyUnitPtr = earthArmy.removeUnit(unitType);
				if (enemyUnitPtr)
					enemyUnits.enqueue(enemyUnitPtr);
			}
			break;
		default:
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
	if (unit->getUnitType() == UnitType::AM)
		alienArmy.removeUnit(UnitType::AM);
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
		default:
			return alienArmy.getUnitsCount(unitType);
	}
}

Game::~Game()
{
	// Delete the random generator
	if (randomGenerator != nullptr)
		delete randomGenerator;
}