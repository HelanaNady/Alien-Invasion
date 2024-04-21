#include "Game.h"
#include "DEFS.h"

int main()
{
    srand((unsigned) time(NULL));

    Game game;
    game.run(GameMode::INTERACTIVE, "testingPhase2.txt");

    return 0;
}
