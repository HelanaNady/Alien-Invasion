#include "Game.h"
#include "DEFS.h"

int main()
{
    // Seed the random number generator
    srand((unsigned) time(NULL));

    // Create a game object and run it
    Game game;
    game.run(GameMode::INTERACTIVE, "InputFiles/neutral.txt");

    return 0;
}