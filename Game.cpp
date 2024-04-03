#include "Game.h"

Game::Game(): gameMode(GameMode::INTERACTIVE), currentTimestep(0)
{
	earthArmy = new EarthArmy();
	alienArmy = new AlienArmy();
	// randomGenerator = new RandomGenerator(); // We need to pass the parameters to the constructor
}

Game::~Game()
{
	delete earthArmy;
	delete alienArmy;
	delete randomGenerator;
}
