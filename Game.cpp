#include "Game.h"

Game::Game(): gameMode(GameMode::INTERACTIVE), currentTimestep(0)
{
	earthArmy = new EarthArmy();
	alienArmy = new AlienArmy();
	randomGenerator = new RandomGenerator();
}

Game::~Game()
{
	delete earthArmy;
	delete alienArmy;
	delete randomGenerator;
}
