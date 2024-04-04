#ifndef GAME_H
#define GAME_H

#include "ArmyClasses/EarthArmy.h"
#include "ArmyClasses/AlienArmy.h"
#include "RandomGenerator/RandomGenerator.h"

enum GameMode
{
	INTERACTIVE,
	SILENT,
};

class Game
{
private:
	GameMode gameMode;
	int currentTimestep;

	EarthArmy earthArmy;
	AlienArmy alienArmy;
	// RandomGenerator randomGenerator; // We need to pass the parameters to the constructor

public:
	Game();

	void run(GameMode);
	void incrementTimestep();
	void changeGameMode(GameMode);

	~Game();
};

#endif