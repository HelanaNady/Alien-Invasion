#include <iostream>

#include "Game.h"
#include "DEFS.h"

void requestValidInput(int&); // Keeps asking the user for an input

int main()
{
    // Seed the random number generator
    srand((unsigned) time(NULL));

    // Welcome message
    std::cout << std::endl << "==================== ALIEN INVASION ====================" << std::endl;
    std::cout << "================= Let the battle begin! ================" << std::endl;

    // Ask the user to choose the game mode
    GameMode gameMode = INTERACTIVE;
    int userChoice = -1;

    std::cout << std::endl;
    std::cout << "How do you want to witness humanity's last stand?" << std::endl;
    std::cout << "[1] Silent Mode --> Silent stealth mission, only output file is generated" << std::endl;
    std::cout << "[2] Interactive Mode --> Do you want the aliens to know you're watching? Press enter for a timestep by step detailed results" << std::endl;
    std::cout << "Enter your choice (1/2): ";

    // Get user choice
    std::cin >> userChoice;

    // Keep asking the user for a valid input
    while (userChoice != 1 && userChoice != 2)
        requestValidInput(userChoice);
    
    // Set the gamemode
    gameMode = userChoice == 1 ? GameMode::SILENT : GameMode::INTERACTIVE;

    // Ask the user to choose the input file
    const int numInputFiles = 3;
    std::string inputFiles[] = { "neutral", "strong_earth", "strong_alien" };
    std::string inputFileName;
    userChoice = -1;

    std::cout << std::endl;
    std::cout << "Choose the input file:" << std::endl;
    std::cout << "[1] Neutral --> Equal strength for both Earth and Aliens" << std::endl;
    std::cout << "[2] Strong Earth --> Earth has a stronger army" << std::endl;
    std::cout << "[3] Strong Aliens --> Aliens have a stronger army" << std::endl;
    std::cout << "Enter your choice (1/2/3): ";

    // Get user choice
    std::cin >> userChoice;

    // Keep asking the user for a valid input
    while (userChoice < 0 || userChoice > numInputFiles)
        requestValidInput(userChoice);

    // Set the input file name
    inputFileName = inputFiles[userChoice - 1]; 

    // Ask the user to choose the output file
    std::string outputFileName;

    std::cout << std::endl;
    std::cout << "Enter the name of the output file (e.g. BattleResults): ";
    std::cin >> outputFileName;

    // Clear the input buffer
    std::cin.ignore();

    // Start the game
    Game game;
    game.run(gameMode, "InputFiles/" + inputFileName + ".txt", outputFileName + ".txt");

    return 0;
}

void requestValidInput(int& userChoice)
{
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    std::cout << "Invalid input. Please enter one of the above options ";
    std::cin >> userChoice;
}
