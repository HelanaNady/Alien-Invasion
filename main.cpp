#include <iostream>

#include "Game.h"
#include "DEFS.h"

void displayWelcomeMessage(); // Displays the welcome message
int requestValidInput(int, int); // Keeps asking the user for an input until a valid one is given
GameMode getUserGameModeChoice(); // Asks the user to choose the game mode and returns the choice
std::string getUserInputFileChoice(); // Asks the user to choose the input file and returns the choice
std::string getUserOutputFileChoice(); // Asks the user to choose the output file and returns the choice

int main()
{
    // Seed the random number generator
    srand((unsigned) time(NULL));

    // Display welcome messages
    displayWelcomeMessage();

    // Get user's choice for game mode
    GameMode gameMode = getUserGameModeChoice();

    // Get user's choice for input file
    std::string inputFileName = getUserInputFileChoice();

    // Get user's choice for output file
    std::string outputFileName = getUserOutputFileChoice();

    // Start the game (made on the heap to avoid stack overflow since the game object is large)
    Game* game = new Game;
    game->run(gameMode, "InputFiles/" + inputFileName + ".txt", outputFileName + ".txt");

    // Delete the game object
    delete game;

    return 0;
}

void displayWelcomeMessage()
{
    std::cout << std::endl << "==================== ALIEN INVASION ===========================" << std::endl;
    std::cout << "================= Let the battle begin! =======================" << std::endl;
}

int requestValidInput(int minChoice, int maxChoice)
{
    int userInput = 0;

    // Generate the options string
    std::string options = "(";
    for (int i = minChoice; i < maxChoice; i++)
        options += std::to_string(i) + "/";
    options += std::to_string(maxChoice) + ")";

    // Ask the user for input
    std::cout << "Enter your choice " << options << ": ";

    // Keep asking the user for input until a valid one is given
    while (!(std::cin >> userInput) || userInput < minChoice || userInput > maxChoice)
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input. Please enter a number from " << options << ": ";
    }

    // Clear the input buffer
    std::cin.ignore();

    return userInput;
}

GameMode getUserGameModeChoice()
{
    std::cout << std::endl;
    std::cout << "How do you want to witness humanity's last stand?" << std::endl;
    std::cout << "[1] Interactive Mode --> Do you want the aliens to know you're watching? Press enter for a timestep by step detailed results" << std::endl;
    std::cout << "[2] Silent Mode --> Silent stealth mission, only output file is generated" << std::endl;

    // Get user choice
    int userChoice = requestValidInput(1, 2);

    return static_cast<GameMode>(userChoice - 1);
}

std::string getUserInputFileChoice()
{
    const int numInputFiles = 3;
    std::string inputFiles[] = { "neutral", "strong_earth", "strong_alien" };

    std::cout << std::endl;
    std::cout << "Choose the input file:" << std::endl;
    std::cout << "[1] Neutral --> Equal strength for both Earth and Aliens" << std::endl;
    std::cout << "[2] Strong Earth --> Earth has a stronger army" << std::endl;
    std::cout << "[3] Strong Aliens --> Aliens have a stronger army" << std::endl;

    // Get user choice
    int userChoice = requestValidInput(1, numInputFiles);

    return inputFiles[userChoice - 1];
}

std::string getUserOutputFileChoice()
{
    std::string outputFileName;

    std::cout << std::endl;
    std::cout << "Enter the name of the output file (e.g. BattleResults): ";
    std::cin >> outputFileName;

    // Clear the input buffer
    std::cin.ignore();

    return outputFileName;
}