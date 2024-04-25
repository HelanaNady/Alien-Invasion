#include "Game.h"
#include "DEFS.h"

int main()
{
    srand((unsigned) time(NULL));

    Game game;
    game.run(GameMode::INTERACTIVE, "C:/Users/ahmed/Desktop/Alien-Invasion/InputFiles/neutral.txt");

    return 0;
}
