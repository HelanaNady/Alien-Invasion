#include <iostream>

#include "Game.h"
#include "DEFS.h"

int main()
{
    srand((unsigned) time(NULL));

    Game game;
    GameMode gameMode;
    int resultOption = 2; // Default mode is interactive mode

    // Get the start of game parameters
    std::cout << "============== AlIENS INVASION, let the battle begin! ==============\n\n";
    std::cout << "How do you want to witness humanity's last stand?\n\n";
    std::cout << "[1] silent mode --> Silent stealth mission, only output file is generated\n";
    std::cout << "[2] interactive mode --> Do you want the aliens to know you're watching?\nPress enter for a timestep by step detailed results\n\n";
    std::cout << "Enter the number of your preferred choice (1/2): \n\n";
    std::cin >> resultOption;

    // Set the start of game parameters 
    gameMode = resultOption == 1 ? SILENT : INTERACTIVE; // Handles invalid input by resetting the mode to default mode
    
    // Start the game
    game.run(gameMode, "InputFiles/strong_earth.txt", "BattleResults.txt");

    return 0;
}
