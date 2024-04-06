#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Game.h"
#include "DEFS.h"
#include "UnitClasses/Unit.h"

std::string Game::loadFile(std::string fileName)
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

Game::Game(): gameMode(GameMode::INTERACTIVE), currentTimestep(0), randomGenerator(nullptr)
{}

void Game::run(GameMode gameMode, std::string inputFileName)
{
	this->gameMode = gameMode;

	std::string inputParameters = loadFile(inputFileName);
	randomGenerator = new RandomGenerator(this, inputParameters);
}

void Game::incrementTimestep()
{}

void Game::changeGameMode(GameMode)
{}

void Game::addUnit(Unit* unit) 
{
	if (unit->getArmyType() == ArmyType::EARTH)
		earthArmy.addUnit(unit);
	else if (unit->getArmyType() == ArmyType::ALIEN)
		alienArmy.addUnit(unit);
}

int Game::getCurrentTimestep()
{
	return currentTimestep;
}

Game::~Game()
{}