#include "Game.h"
#include "DEFS.h"

int main()
{
    srand((unsigned) time(NULL));

    Game game;
    game.run(GameMode::INTERACTIVE, "InputFiles/strong_earth.txt", "BattleResults.txt");

    return 0;
}
