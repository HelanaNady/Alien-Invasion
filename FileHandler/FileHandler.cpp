#include <fstream>

#include "FileHandler.h"

std::string FileHandler::loadFile(std::string fileName)
{
	std::fstream fin(fileName);
	std::string wholeFile;

	if (fin.is_open())
	{
		std::string newLine;
		while (std::getline(fin, newLine))
			wholeFile += newLine + " ";
	}
    
	return wholeFile;
}

void FileHandler::outputFile(std::string outputFileName, std::string content)
{
    //
}

