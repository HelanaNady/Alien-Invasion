#include <iostream>

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

		std::cout << "\nCurrent Timestep " << currentTimestep << std::endl;
		earthArmy.print();
		alienArmy.print();
		printKilledList();
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

void Game::killUnit(Unit* unit)
{
	killedList.enqueue(unit);
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
{
	// Delete the random generator
	if (randomGenerator != nullptr)
		delete randomGenerator;

	// Delete all units in the killed list
	Unit* unit = nullptr;
	while (!killedList.isEmpty())
	{
		killedList.dequeue(unit);
		delete unit;
	}
}