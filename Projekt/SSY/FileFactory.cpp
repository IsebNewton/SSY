#include "FileFactory.h"
#include <fstream>
#include <SDL.h>

void FileFactory::writeLine(std::string file, std::string text, const char mode)
{
	std::ofstream destinationFile;
	destinationFile.open(file, mode);

	if (!destinationFile.is_open())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Datei %s konnte nicht geöffnet werden", file);
	}
	else
	{
		destinationFile << text;
		if (text.substr(text.size() - 1) != "\n")
		{
			destinationFile << "\n";
		}

		destinationFile.close();
		if (destinationFile.is_open())
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Datei %s konnte nicht geschlossen werden", file);
		}
	}

}

std::list<std::string> FileFactory::readLines(std::string file)
{
	std::list<std::string> linesList;
	std::ifstream destinationFile;
	destinationFile.open(file);
	if (!destinationFile.is_open())
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Datei %s konnte nicht geöffnet werden", file);
	}
	else
	{
		while (!destinationFile.eof())
		{
			std::string line;
			std::getline(destinationFile, line);
			if (line.length() > 0 && line.at(0) != '#')
			{
				linesList.push_back(line);
			}
		}

		destinationFile.close();
		if (destinationFile.is_open())
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Datei %s konnte nicht geschlossen werden", file);
		}
	}

	return linesList;
}

std::map<std::string, std::string> FileFactory::read(std::string file)
{
	std::map<std::string, std::string> resultMap;
	std::list<std::string> lines = readLines(file);

	for (std::list<std::string>::iterator it = lines.begin(); it != lines.end(); ++it)
	{
		std::string line = (*it);
		std::string key = line.substr(0, line.find('='));
		// Trim String
		key.erase(0, key.find_first_not_of(" "));
		key.erase(key.find_last_not_of(" ") + 1);

		std::string value = line.substr(line.find('=') + 1);
		// Trim String
		value.erase(0, value.find_first_not_of(" "));
		value.erase(value.find_last_not_of(" ") + 1);

		resultMap.insert(std::pair<std::string, std::string>(key, value));
	}

	return resultMap;
}
