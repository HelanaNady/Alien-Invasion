#include <iostream>

#include "Game.h"
#include "DEFS.h"

int main()
{
    // Seed the random number generator
    srand((unsigned) time(NULL));

    // Welcome message
    std::cout << std::endl << "==================== ALIEN INVASION ====================" << std::endl;
    std::cout << "================= Let the battle begin! ================" << std::endl;

    // Ask the user to choose the game mode
    GameMode gameMode = INTERACTIVE; // Default mode is interactive mode
    int resultOption = 2; // Default mode is interactive mode

    std::cout << std::endl;
    std::cout << "How do you want to witness humanity's last stand?" << std::endl;
    std::cout << "[1] Silent Mode --> Silent stealth mission, only output file is generated" << std::endl;
    std::cout << "[2] Interactive Mode --> Do you want the aliens to know you're watching? Press enter for a timestep by step detailed results" << std::endl;
    std::cout << "Enter your choice (1/2): ";
    std::cin >> resultOption;

    // Set the start of game parameters 
    gameMode = resultOption == 1 ? SILENT : INTERACTIVE; // Handles invalid input by resetting the mode to default mode

    // Clear the input buffer
    std::cin.ignore();

    // Start the game
    Game game;
    game.run(gameMode, "InputFiles/neutral.txt", "BattleResults.txt");

    return 0;
}