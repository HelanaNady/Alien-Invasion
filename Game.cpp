#include <iostream>
#include <fstream>

#include "Game.h"
#include "DEFS.h"
#include "UnitClasses/Unit.h"

Game::Game(): gameMode(GameMode::INTERACTIVE), currentTimestep(0), earthArmy(this), alienArmy(this), randomGenerator(this)
{}

void Game::run(GameMode gameMode, std::string inputFileName, std::string outputFileName)
{
	// Change the game mode 
	setGameMode(gameMode);

	// Load the parameters from the file and set the parameters in the random generator
	if (!loadParameters(inputFileName)) // If the file is not found, print an error message and return
	{
		std::cout << "Error: File not found!" << std::endl;
		return;
	}

	// Run the game
	bool didArmiesAttack = true;
	do
	{
		// Increment Timestep
		currentTimestep++;

		// Generate units for both armies
		randomGenerator.generateUnits();

		// Start fight
		didArmiesAttack = startAttack();

		// Print the output
		if (gameMode == GameMode::INTERACTIVE)
			printAll();

		std::cout << "Press Enter to continue...";
		while (std::cin.get() != '\n');
	} while (!battleOver(didArmiesAttack));

	// Produce the output file
	generateOutputFile(outputFileName);
}

bool Game::startAttack()
{
	// Returns a boolean indicating whether any army attacked 
	return earthArmy.attack() || alienArmy.attack();
}

void Game::setGameMode(GameMode gameMode)
{
	this->gameMode = gameMode;
}

bool Game::battleOver(bool didArmiesAttack) const
{
	return currentTimestep >= 40 && (earthArmy.isDead() || alienArmy.isDead() || !didArmiesAttack);
}

std::string Game::battleResult() const
{
	if (earthArmy.isDead() && !alienArmy.isDead())
		return "Alien Army wins!";
	else if (!earthArmy.isDead() && alienArmy.isDead())
		return "Earth Army wins!";
	else
		return "Drawn!";
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

void Game::addUnitToMaintenanceList(Unit* unit)
{
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

	return unitsToMaintain;
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

GameStatistics Game::countStatistics()
{
	GameStatistics gameStatistics = { { 0 }, 0, 0, { 0 }, 0, 0, 0, 0, 0, 0, 0 };

	Unit* unit = nullptr;

	// Earth Army Statistics
	UnitType earthUnitTypes[4] = { UnitType::ES, UnitType::ET, UnitType::EG, UnitType::EH };

	for (int i = 0; i < 4; i++)
	{
		int count = getUnitsCount(ArmyType::EARTH, earthUnitTypes[i]);

		for (int j = 0; j < count; j++)
		{
			unit = earthArmy.removeUnit(earthUnitTypes[i]);

			// Unit Counts
			gameStatistics.unitCounts[earthUnitTypes[i]]++;
			gameStatistics.totalEarthUnitsCount++;

			// Delays
			gameStatistics.totalEarthFirstAttackDelays += unit->getFirstAttackDelay();

			addUnit(unit);

			// Nullify the pointer
			unit = nullptr;
		}
	}

	// Alien Army Statistics
	UnitType alienUnitTypes[3] = { UnitType::AS, UnitType::AM, UnitType::AD };

	for (int i = 0; i < 3; i++)
	{
		int count = getUnitsCount(ArmyType::ALIEN, alienUnitTypes[i]);

		for (int j = 0; j < count; j++)
		{
			unit = alienArmy.removeUnit(alienUnitTypes[i]);

			// Unit Counts
			gameStatistics.unitCounts[alienUnitTypes[i]]++;
			gameStatistics.totalAlienUnitsCount++;

			// Delays
			gameStatistics.totalAlienFirstAttackDelays += unit->getFirstAttackDelay();

			addUnit(unit);

			// Nullify the pointer
			unit = nullptr;
		}
	}

	// Killed Units Statistics
	int count = killedList.getCount();

	for (int i = 0; i < count; i++)
	{
		killedList.dequeue(unit);
		UnitType unitType = unit->getUnitType();

		// Unit Counts
		gameStatistics.unitCounts[unitType]++;
		gameStatistics.totalAlienUnitsCount++;

		// Destructed Unit Counts
		gameStatistics.destructedUnitCounts[unitType]++;
		gameStatistics.totalDestructedUnitsCount++;

		// Delays
		if (unit->getArmyType() == ArmyType::EARTH)
		{
			gameStatistics.totalEarthFirstAttackDelays += unit->getFirstAttackDelay();
			gameStatistics.totalEarthBattleDelays += unit->getBattleDelay();
			gameStatistics.totalEarthDestructionDelays += unit->getDestructionDelay();
		}
		else if (unit->getArmyType() == ArmyType::ALIEN)
		{
			gameStatistics.totalAlienFirstAttackDelays += unit->getFirstAttackDelay();
			gameStatistics.totalAlienBattleDelays += unit->getBattleDelay();
			gameStatistics.totalAlienDestructionDelays += unit->getDestructionDelay();
		}

		killedList.enqueue(unit);

		// Nullify the pointer
		unit = nullptr;
	}

	return gameStatistics;
}

void Game::generateOutputFile(std::string outputFileName)
{
	// Open the output file
	std::ofstream fout(outputFileName);

	// Count the statistics
	GameStatistics gameStatistics = countStatistics();

	// Print the header
	fout << "Td\tID\t\tTj\tDf\tDd\tDb" << std::endl;

	// Print the killed units
	Unit* killedUnit = nullptr;
	for (int i = 0; i < gameStatistics.totalDestructedUnitsCount; i++)
	{
		killedList.dequeue(killedUnit);
		fout << killedUnit->getDestructionTime() << "\t" << killedUnit->getId() << "\t" << killedUnit->getJoinTime() << "\t"
			<< killedUnit->getFirstAttackDelay() << "\t" << killedUnit->getDestructionDelay() << "\t" << killedUnit->getBattleDelay() << std::endl;
		killedList.enqueue(killedUnit);
	}

	// Print the battle result
	fout << std::endl << "Battle Result " << battleResult() << std::endl;

	// Earth Army Statistics
	fout << std::endl << "Earth Army Statistics:" << std::endl;

	fout << "Total ES Count: " << gameStatistics.unitCounts[UnitType::ES] << std::endl;
	fout << "Total ET Count: " << gameStatistics.unitCounts[UnitType::ET] << std::endl;
	fout << "Total EG Count: " << gameStatistics.unitCounts[UnitType::EG] << std::endl;
	fout << "Total EH Count: " << gameStatistics.unitCounts[UnitType::EH] << std::endl;

	fout << "Destructed ESs/Total ESs = " << (gameStatistics.unitCounts[UnitType::ES] != 0 ? ((float) gameStatistics.destructedUnitCounts[UnitType::ES] / gameStatistics.unitCounts[UnitType::ES] * 100) : 0) << "%" << std::endl;
	fout << "Destructed ETs/Total ETs = " << (gameStatistics.unitCounts[UnitType::ET] != 0 ? ((float) gameStatistics.destructedUnitCounts[UnitType::ET] / gameStatistics.unitCounts[UnitType::ET] * 100) : 0) << "%" << std::endl;
	fout << "Destructed EGs/Total EGs = " << (gameStatistics.unitCounts[UnitType::EG] != 0 ? ((float) gameStatistics.destructedUnitCounts[UnitType::EG] / gameStatistics.unitCounts[UnitType::EG] * 100) : 0) << "%" << std::endl;

	fout << "Total Destructed Earth Units/Total Units = " << (gameStatistics.totalEarthUnitsCount != 0 ? ((float) gameStatistics.totalDestructedUnitsCount / gameStatistics.totalEarthUnitsCount) : 0) << "%" << std::endl;

	fout << "Average of First Attack Delay = " << (gameStatistics.totalEarthUnitsCount != 0 ? ((float) gameStatistics.totalEarthFirstAttackDelays / gameStatistics.totalEarthUnitsCount) : 0) << std::endl;
	fout << "Average of Destruction Delay = " << (gameStatistics.totalEarthUnitsCount != 0 ? ((float) gameStatistics.totalEarthDestructionDelays / gameStatistics.totalEarthUnitsCount) : 0) << std::endl;
	fout << "Average of Battle Delay = " << (gameStatistics.totalEarthUnitsCount != 0 ? ((float) gameStatistics.totalEarthBattleDelays / gameStatistics.totalEarthUnitsCount) : 0) << std::endl;

	fout << "Df/Db = " << (gameStatistics.totalEarthBattleDelays != 0 ? ((float) gameStatistics.totalEarthFirstAttackDelays / gameStatistics.totalEarthBattleDelays * 100) : 0) << "%" << std::endl;
	fout << "Dd/Db = " << (gameStatistics.totalEarthBattleDelays != 0 ? ((float) gameStatistics.totalEarthDestructionDelays / gameStatistics.totalEarthBattleDelays * 100) : 0) << "%" << std::endl;

	// Alien Army Statistics
	fout << std::endl << "Alien Army Statistics:" << std::endl;

	fout << "Total AS Count: " << gameStatistics.unitCounts[UnitType::AS] << std::endl;
	fout << "Total AM Count: " << gameStatistics.unitCounts[UnitType::AM] << std::endl;
	fout << "Total AD Count: " << gameStatistics.unitCounts[UnitType::AD] << std::endl;

	fout << "Destructed ASs/Total ASs = " << (gameStatistics.unitCounts[UnitType::AS] != 0 ? ((float) gameStatistics.destructedUnitCounts[UnitType::AS] / gameStatistics.unitCounts[UnitType::AS] * 100) : 0) << "%" << std::endl;
	fout << "Destructed AMs/Total AMs = " << (gameStatistics.unitCounts[UnitType::AM] != 0 ? ((float) gameStatistics.destructedUnitCounts[UnitType::AM] / gameStatistics.unitCounts[UnitType::AM] * 100) : 0) << "%" << std::endl;
	fout << "Destructed ATs/Total ATs = " << (gameStatistics.unitCounts[UnitType::AD] != 0 ? ((float) gameStatistics.destructedUnitCounts[UnitType::AD] / gameStatistics.unitCounts[UnitType::AD] * 100) : 0) << "%" << std::endl;

	fout << "Total Destructed Alien Units/Total Units = " << (gameStatistics.totalAlienUnitsCount != 0 ? ((float) gameStatistics.totalDestructedUnitsCount / gameStatistics.totalAlienUnitsCount) : 0) << "%" << std::endl;

	fout << "Average of First Attack Delay = " << (gameStatistics.totalAlienUnitsCount != 0 ? ((float) gameStatistics.totalAlienFirstAttackDelays / gameStatistics.totalAlienUnitsCount) : 0) << std::endl;
	fout << "Average of Destruction Delay = " << (gameStatistics.totalAlienUnitsCount != 0 ? ((float) gameStatistics.totalAlienDestructionDelays / gameStatistics.totalAlienUnitsCount) : 0) << std::endl;
	fout << "Average of Battle Delay = " << (gameStatistics.totalAlienUnitsCount != 0 ? ((float) gameStatistics.totalAlienBattleDelays / gameStatistics.totalAlienUnitsCount) : 0) << std::endl;

	fout << "Df/Db = " << (gameStatistics.totalAlienBattleDelays != 0 ? ((float) gameStatistics.totalAlienFirstAttackDelays / gameStatistics.totalAlienBattleDelays * 100) : 0) << "%" << std::endl;
	fout << "Dd/Db = " << (gameStatistics.totalAlienBattleDelays != 0 ? ((float) gameStatistics.totalAlienDestructionDelays / gameStatistics.totalAlienBattleDelays * 100) : 0) << "%" << std::endl;

	// Close the output file
	fout.close();
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
{
	Unit* unit = nullptr;
	int dummyPri = 0;

	// Delete the units in the killed list
	while (killedList.dequeue(unit))
	{
		delete unit;
		unit = nullptr;
	}

	// Delete the units in the maintenance list
	while (unitMaintenanceList.dequeue(unit, dummyPri))
	{
		delete unit;
		unit = nullptr;
	}
}