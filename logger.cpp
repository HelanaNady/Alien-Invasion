#include <sstream>

#include "Logger.h"
#include "Game.h"

Logger::Logger(Game* gamePtr, const std::string filename): gamePtr(gamePtr)
{
    latestTimestep = -1;
    // Clear the log file
    std::ofstream clearFile(filename, std::ios::out | std::ios::trunc);
    clearFile.close();

    // Open the log file
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open())
        std::cout << "Error opening log file." << std::endl;

}

void Logger::log(std::string message)
{
    if (latestTimestep != gamePtr->getCurrentTimestep())
        addBreakLine();

    latestTimestep = gamePtr->getCurrentTimestep();
    // Log the message with the current timestep
    std::ostringstream logEntry;
    logEntry << "[" << gamePtr->getCurrentTimestep() << "]: " << message << std::endl;

    // Write the log to the file
    if (logFile.is_open())
    {
        logFile << logEntry.str();
        logFile.flush();
    }
}

void Logger::addBreakLine()
{
    logFile << "============================================================================" << std::endl;
}

Logger::~Logger() 
{ 
    std::cout << "log destructor was called \n";
    logFile.close(); 
}