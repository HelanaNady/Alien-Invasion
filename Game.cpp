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
		if(gameMode == GameMode::INTERACTIVE)
			printAll();
		//printOutputFile();
	}
}

void Game::incrementTimestep()
{
	currentTimestep++;

	// Generate units for both armies
	randomGenerator->generateArmy(ArmyType::EARTH);
	randomGenerator->generateArmy(ArmyType::ALIEN);
}

void Game::changeGameMode(GameMode gameMode)
{
	this->gameMode = gameMode;
}

bool Game::battleOver() const
{
	return currentTimestep > 10;
}

void Game::addUnit(Unit* unit)
{
	if (unit->getArmyType() == ArmyType::EARTH)
		earthArmy.addUnit(unit);
	else if (unit->getArmyType() == ArmyType::ALIEN)
		alienArmy.addUnit(unit);
}

Unit* Game::removeUnit(ArmyType armyType, UnitType unitType)
{
	switch (armyType)
	{
		case (ArmyType::EARTH):
			return earthArmy.removeUnit(unitType);
			break;
		default:
			return alienArmy.removeUnit(unitType);
			break;

	}
}

void Game::killUnit(Unit* unit)
{
	killedList.enqueue(unit); 
}

void Game::printAll() 
{
	std::cout << "\nCurrent Timestep " << currentTimestep << std::endl;
	earthArmy.printArmy();
	alienArmy.printArmy();
	
	std::cout << "============== Units fighting at current step ==============" << std::endl;
	earthArmy.printFightingUnits(); // Is this right?
	alienArmy.printFightingUnits();

	printKilledList();
}

void Game::printKilledList() const
{
	std::cout << "============== Killed/Destructed Units ==============" << std::endl;
	std::cout << killedList.getCount() << " units [";
	killedList.printList();
	std::cout << "]" << std::endl;
}


int Game::getCurrentTimestep() const
{
	return currentTimestep;
}

Game::~Game()
{}