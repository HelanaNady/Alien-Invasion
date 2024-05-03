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
    GameMode gameMode = INTERACTIVE;
    int resultOption = -1;

    std::cout << std::endl;
    std::cout << "How do you want to witness humanity's last stand?" << std::endl;
    std::cout << "[1] Silent Mode --> Silent stealth mission, only output file is generated" << std::endl;
    std::cout << "[2] Interactive Mode --> Do you want the aliens to know you're watching? Press enter for a timestep by step detailed results" << std::endl;
    std::cout << "Enter your choice (1/2): ";

    while (resultOption != 1 && resultOption != 2)
    {
        std::cin >> resultOption;
        if (resultOption == 1)
            gameMode = GameMode::SILENT;
        else if (resultOption == 2)
            gameMode = GameMode::INTERACTIVE;
        else
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter 1 or 2: ";
        }
    }

    // Clear the input buffer
    std::cin.ignore();

    // Ask the user to choose the input file
    std::string inputFileName;
    std::cout << std::endl;
    std::cout << "Enter the name of the input file (e.g. InputFiles/neutral.txt): ";
    std::cin >> inputFileName;

    // Ask the user to choose the output file
    std::string outputFileName;
    std::cout << "Enter the name of the output file (e.g. BattleResults.txt): ";
    std::cin >> outputFileName;

    // Clear the input buffer
    std::cin.ignore();

    // Start the game
    Game game;
    game.run(gameMode, inputFileName, outputFileName);

    return 0;
}