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
	char key = '\0';

	do {
		incrementTimestep();

		std::cout << "\nCurrent Timestep " << currentTimestep << std::endl;
		earthArmy.print();
		alienArmy.print();
		printKilledList();

		std::cout << "Click enter to continue...";
		while (key != '\n')
			std::cin >> key;
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
		Unit* unit = earthArmy.removeUnit(UnitType::ES);
		if (unit)
			addUnit(unit);
	}
	else if (x < 20)
	{
		Unit* unit = earthArmy.removeUnit(UnitType::ET);
		if (unit)
			killUnit(unit);
	}
	else if (x < 30)
	{
		Unit* unit = earthArmy.removeUnit(UnitType::EG);
		if (unit)
		{
			unit->setHealth(0.5 * unit->getHealth());
			earthArmy.addUnit(unit);
		}
	}
	else if (x < 40)
	{
		LinkedQueue<Unit*> tempList;
		Unit* unit = nullptr;
		for (int i = 0; i < 5; i++)
		{
			unit = alienArmy.removeUnit(UnitType::AS);
			if (unit)
			{
				int newHealth = unit->getHealth() - 1;
				if (newHealth > 0)
				{
					unit->recieveDamage(newHealth);
					tempList.enqueue(unit);
				}
			}
		}

		while(tempList.dequeue(unit))
		{
			alienArmy.addUnit(unit);
		}
	}
	else if (x < 50)
	{
		LinkedQueue<Unit*> removedMonsters;
		for (int i = 0; i < 5; i++)
		{
			Unit* unit = alienArmy.removeUnit(UnitType::AM);
			if (unit)
				removedMonsters.enqueue(unit); // Removed 5 or less Monsters
		}

		for (int i = 0; i < removedMonsters.getCount(); i++)
		{
			Unit* removedMonster = nullptr;
			removedMonsters.dequeue(removedMonster);
			alienArmy.addUnit(dynamic_cast<AlienMonster*>(removedMonster)); // Re-added 5 Monsters
		}
	}
	else if (x < 60)
	{
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