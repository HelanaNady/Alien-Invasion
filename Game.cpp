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
	do
	{
		incrementTimestep();

		// Print the current timestep and the armies and the killed list
		std::cout << "\nCurrent Timestep " << currentTimestep << std::endl;
		earthArmy.print();
		alienArmy.print();
		printKilledList();

		// Wait for the user to press Enter
		std::cout << "Press Enter to continue...";
		while (std::cin.get() != '\n');
	} while (!battleOver());
}

void Game::incrementTimestep()
{
	currentTimestep++;

	// Generate units for both armies
	randomGenerator->generateArmy(ArmyType::EARTH);
	randomGenerator->generateArmy(ArmyType::ALIEN);

	// Generate random number X
	int x = randomGenerator->getRandomNumber(1, 100);
	if (x < 10)
	{
		// Remove a soldier from the Earth army and add it back
		Unit* unit = earthArmy.removeUnit(UnitType::ES);
		if (unit)
			earthArmy.addUnit(unit);
	}
	else if (x < 20)
	{
		// Remove a tank from the Earth army and added to the killed list
		Unit* unit = earthArmy.removeUnit(UnitType::ET);
		if (unit)
			killUnit(unit);
	}
	else if (x < 30)
	{
		// Remove a gunner from the Earth army, reduce its health by half, and add it back
		Unit* unit = earthArmy.removeUnit(UnitType::EG);
		if (unit)
		{
			unit->receiveDamage(0.5 * unit->getHealth()); // Reduce health by half
			earthArmy.addUnit(unit);
		}
	}
	else if (x < 40)
	{
		// Remove 5 soldiers from the Alien army, reduce their health by 1, and add them back
		LinkedQueue<Unit*> tempList;
		Unit* unit = nullptr;

		// Remove 5 soldiers
		for (int i = 0; i < 5; i++)
		{
			unit = alienArmy.removeUnit(UnitType::AS);

			if (unit)
			{
				unit->receiveDamage(1); // Reduce health by 1
				tempList.enqueue(unit);
			}
		}

		// Add the units back
		while (tempList.dequeue(unit))
			if (unit->isAlive())
				alienArmy.addUnit(unit);
			else
				killUnit(unit);
	}
	else if (x < 50)
	{
		// Remove 5 monsters from the Alien army and add them back
		LinkedQueue<Unit*> removedMonsters;
		Unit* unit = nullptr;

		// Remove 5 Monsters
		for (int i = 0; i < 5; i++)
		{
			unit = alienArmy.removeUnit(UnitType::AM);
			if (unit)
				removedMonsters.enqueue(unit);
		}

		// Add 5 Monsters back
		while (removedMonsters.dequeue(unit))
			alienArmy.addUnit(unit);
	}
	else if (x < 60)
	{
		// Remove 6 drones from the front & back of the list of Alien army and add them to the killed list
		for (int i = 0; i < 6; i++)
		{
			Unit* unit = alienArmy.removeUnit(UnitType::AD);
			if (unit)
				killUnit(unit);
		}
	}
}

void Game::changeGameMode(GameMode gameMode)
{
	this->gameMode = gameMode;
}

bool Game::battleOver() const
{
	return currentTimestep >= 50;
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

	// Delete all units in the killed list
	Unit* unit = nullptr;
	while (!killedList.isEmpty())
	{
		killedList.dequeue(unit);
		delete unit;
	}
}