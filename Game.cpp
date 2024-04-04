#include "Game.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 

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
	randomGenerator = new RandomGenerator(inputParameters);
};

Game::~Game()
{}
