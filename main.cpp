#include "Game.h"
#include "DEFS.h"

int main()
{
    // Seed the random number generator
    srand((unsigned) time(NULL));

    // Create a game object and run it
    Game game;
    game.run(GameMode::INTERACTIVE, "phase1testing.txt");

    return 0;
}