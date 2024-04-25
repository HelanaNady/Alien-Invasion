#include <iostream>
#include <fstream>

#include "Game.h"
#include "DEFS.h"
#include "UnitClasses/Unit.h"

Game::Game(): gameMode(GameMode::INTERACTIVE), currentTimestep(0), earthArmy(this), alienArmy(this), randomGenerator(this), logger(this, "log.txt")
{}

void Game::run(GameMode gameMode, std::string inputFileName)
{
	logStartOfGame();

	// Change the game mode
	setGameMode(gameMode);
	logger.log("Game mode changed to " + gameModeToString(gameMode));

	// Load the parameters from the file and set the parameters in the random generator
	if (!loadParameters(inputFileName)) // If the file is not found, print an error message and return
	{
		std::cout << "Error: File not found!" << std::endl;
		return;
	}
	logger.log("Parameters loaded from file " + inputFileName);

	// Run the game
	do
	{
		incrementTimestep();

		// Print the output
		logger.log("Printing output...");
		if (gameMode == GameMode::INTERACTIVE)
			printAll();

		std::cout << "Press Enter to continue...";
		while (std::cin.get() != '\n');
	} while (!battleOver());

	logEndOfGame();
}

std::string Game::gameModeToString(GameMode gameMode)
{
	switch (gameMode)
	{
		case GameMode::INTERACTIVE:
			return "Interactive";
		case GameMode::SILENT:
			return "Silent";
	}

	return "Unknown";
}

void Game::incrementTimestep()
{
	currentTimestep++;

	logBeginOfTimeStep();

	// Generate units for both armies
	randomGenerator.generateUnits();

	// Start the battle attack
	logger.log("Earth Army attacking...");
	earthArmy.attack();
	logger.log("Alien Army attacking...");
	alienArmy.attack();

	logEndOfTimeStep();
}

void Game::setGameMode(GameMode gameMode)
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

	if (unit)
		logger.log("Adding unit: " + unit->toString());
	else
		logger.log("Adding unit: nullptr");

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

	if (enemyUnits.getCount() == 0)
		logger.log(Unit::unitTypeString(unitType) + " to attack: []");
	else
	{
		logger.log(Unit::unitTypeString(unitType) + " to attack: [");
		for (int i = 0; i < enemyUnits.getCount(); i++)
		{
			Unit* unit = nullptr;
			enemyUnits.dequeue(unit);
			logger.log(unit->toString());
			enemyUnits.enqueue(unit);
		}
		logger.log("]");
	}

	return enemyUnits;
}

void Game::addUnitToMaintenanceList(Unit* unit)
{
	if (unit)
		logger.log("Adding unit to maintenance list: " + unit->toString());
	else
		logger.log("Adding unit to maintenance list: nullptr");

	if (unit->getUnitType() == UnitType::ES)
	{
		unit->setUMLjoinTime(currentTimestep); // Set the time when the unit joined the UML
		unitMaintenanceList.enqueue(unit, dynamic_cast<EarthSoldier*>(unit)->getHealPriority());
	}
	else if (unit->getUnitType() == UnitType::ET)
	{
		unit->setUMLjoinTime(currentTimestep); // Set the time when the unit joined the UML
		unitMaintenanceList.enqueue(unit, dynamic_cast<EarthTank*>(unit)->getHealPriority());
	}
}

LinkedQueue<Unit*> Game::getUnitsToMaintainList(int attackCapacity)
{
	LinkedQueue<Unit*> unitsToMaintain;

	Unit* unit = nullptr;
	int dummyPri = 0;
	for (int i = 0; i < attackCapacity; i++)
	{
		unit = nullptr;
		if (unitMaintenanceList.dequeue(unit, dummyPri))
			unitsToMaintain.enqueue(unit);
		else
			break;
	}

	logger.log("Units to maintain: " + std::to_string(unitsToMaintain.getCount()));
	logger.log("Units to maintain: [");
	for (int i = 0; i < unitsToMaintain.getCount(); i++)
	{
		Unit* unit = nullptr;
		unitsToMaintain.dequeue(unit);
		logger.log(unit->toString());
		unitsToMaintain.enqueue(unit);
	}
	logger.log("]");

	return unitsToMaintain;
}

void Game::logStartOfGame()
{
	logger.log("Game started.");
}

void Game::logBeginOfTimeStep()
{
	logger.log("Begin of timestep.");
}

void Game::addToKilledList(Unit* unit)
{
	logger.log("Adding unit to killed list: " + unit->toString());
	killedList.enqueue(unit);
}

void Game::log(std::string message)
{
	logger.log(message);
}

void Game::logEndOfTimeStep()
{
	logger.log("End of timestep.");
}

void Game::logEndOfGame()
{
	logger.log("Game ended.");
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

	std::cout << "============== Maintenance List Units ==============" << std::endl;
	printUnitMaintenanceList();

	std::cout << "============== Killed/Destructed Units ==============" << std::endl;
	printKilledList();
}

void Game::printKilledList() const
{
	std::cout << killedList.getCount() << " units [";
	killedList.printList();
	std::cout << "]" << std::endl;
}

void Game::printUnitMaintenanceList() const
{
	std::cout << unitMaintenanceList.getCount() << " units [";
	unitMaintenanceList.printList();
	std::cout << "]" << std::endl;
}

bool Game::loadParameters(std::string fileName)
{
	std::fstream fin(fileName);

	if (fin.is_open())
	{
		int N = 0;
		int ESPercentage = 0;
		int ETPercentage = 0;
		int EGPercentage = 0;
		int ASPercentage = 0;
		int AMPercentage = 0;
		int ADPercentage = 0;
		int EHPercentage = 0;
		int prob = 0;
		Range earthPowerRange = { 0, 0 };
		Range earthHealthRange = { 0, 0 };
		Range earthAttackCapacityRange = { 0, 0 };
		Range alienPowerRange = { 0, 0 };
		Range alienHealthRange = { 0, 0 };
		Range alienAttackCapacityRange = { 0, 0 };

		fin >> N >> ESPercentage >> ETPercentage >> EGPercentage >> ASPercentage >> AMPercentage >> ADPercentage >> EHPercentage >> prob;

		char dummyHyphen; // Dummy variable to read the hyphen

		fin >> earthPowerRange.min >> dummyHyphen >> earthPowerRange.max;
		fin >> earthHealthRange.min >> dummyHyphen >> earthHealthRange.max;
		fin >> earthAttackCapacityRange.min >> dummyHyphen >> earthAttackCapacityRange.max;

		fin >> alienPowerRange.min >> dummyHyphen >> alienPowerRange.max;
		fin >> alienHealthRange.min >> dummyHyphen >> alienHealthRange.max;
		fin >> alienAttackCapacityRange.min >> dummyHyphen >> alienAttackCapacityRange.max;

		randomGenerator.setN(N); // Set the number of units to generate
		randomGenerator.setProb(prob); // Set the probability of generating a unit

		randomGenerator.setEarthParameters(ESPercentage, EGPercentage, ETPercentage, EHPercentage, earthPowerRange, earthHealthRange, earthAttackCapacityRange); // Set the parameters for the Earth army
		randomGenerator.setAlienParameters(ASPercentage, AMPercentage, ADPercentage, alienPowerRange, alienHealthRange, alienAttackCapacityRange); // Set the parameters for the Alien army

		fin.close(); // Close the file

		return true; // File loaded successfully
	}

	return false; // File failed to load
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