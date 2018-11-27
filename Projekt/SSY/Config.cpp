#include "Config.h"
#include "FileFactory.h"

std::map<Config::ConfigAttributes, std::string> Config::attributeNames =
{
	{ Config::ConfigAttributes::FULLSCREEN , "Fullscreen" },
	{ Config::ConfigAttributes::WINDOW_WIDTH , "Windowwidth" },
	{ Config::ConfigAttributes::WINDOW_HEIGHT , "Windowheight" },

	{ Config::ConfigAttributes::MUSIC_ON , "Music" },
	{ Config::ConfigAttributes::SOUND_ON , "Sound" },
	{ Config::ConfigAttributes::MUSIC_VOLUME , "Musicvolume" },
	{ Config::ConfigAttributes::SOUND_VOLUME , "Soundvolume" }
};

std::map<std::string, Config::ConfigAttributes> Config::nameAttributes =
{
	{ "Fullscreen" , Config::ConfigAttributes::FULLSCREEN },
	{ "Windowwidth" , Config::ConfigAttributes::WINDOW_WIDTH },
	{ "Windowheight" , Config::ConfigAttributes::WINDOW_HEIGHT },

	{ "Music" , Config::ConfigAttributes::MUSIC_ON },
	{ "Sound" , Config::ConfigAttributes::SOUND_ON },
	{ "Musicvolume" , Config::ConfigAttributes::MUSIC_VOLUME },
	{ "Soundvolume" , Config::ConfigAttributes::SOUND_VOLUME }
};

bool Config::fullscreen;
int Config::windowWidth;
int Config::windowHeight;

bool Config::musicOn;
bool Config::soundOn;
int Config::musicVolume;
int Config::soundVolume;

float Config::menuHeight = 0.2;		// 20% für das Menü

void Config::setAttribut(Config::ConfigAttributes attribut, std::string value)
{
	try
	{
		switch (attribut)
		{
		case ConfigAttributes::FULLSCREEN:
			fullscreen = std::stoi(value);
			break;
		case ConfigAttributes::WINDOW_WIDTH:
			windowWidth = std::stoi(value);
			break;
		case ConfigAttributes::WINDOW_HEIGHT:
			windowHeight = std::stoi(value);
			break;
		case ConfigAttributes::MUSIC_ON:
			musicOn = std::stoi(value);
			break;
		case ConfigAttributes::SOUND_ON:
			soundOn = std::stoi(value);
			break;
		case ConfigAttributes::MUSIC_VOLUME:
			musicVolume = std::stoi(value);
			break;
		case ConfigAttributes::SOUND_VOLUME:
			soundVolume = std::stoi(value);
			break;
		}
	}
	catch (const std::exception &e)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, e.what());
	}
}

void Config::save()
{
	std::map<std::string, std::string> map;
	std::string file = "config/config.txt";

	map.insert(std::pair<std::string, std::string>(
		Config::attributeNames.at(ConfigAttributes::FULLSCREEN), std::to_string(fullscreen)));
	map.insert(std::pair<std::string, std::string>(
		Config::attributeNames.at(ConfigAttributes::WINDOW_WIDTH), std::to_string(windowWidth)));
	map.insert(std::pair<std::string, std::string>(
		Config::attributeNames.at(ConfigAttributes::WINDOW_HEIGHT), std::to_string(windowHeight)));
	map.insert(std::pair<std::string, std::string>(
		Config::attributeNames.at(ConfigAttributes::MUSIC_ON), std::to_string(musicOn)));
	map.insert(std::pair<std::string, std::string>(
		Config::attributeNames.at(ConfigAttributes::SOUND_ON), std::to_string(soundOn)));
	map.insert(std::pair<std::string, std::string>(
		Config::attributeNames.at(ConfigAttributes::MUSIC_VOLUME), std::to_string(musicVolume)));
	map.insert(std::pair<std::string, std::string>(
		Config::attributeNames.at(ConfigAttributes::SOUND_VOLUME), std::to_string(soundVolume)));

	FileFactory::writeLine(file, "### Config ###\n\n", std::ios::beg);
	FileFactory::write(file, map);
}

void Config::readConfig()
{
	std::map<std::string, std::string> lines = FileFactory::read("config/config.txt");

	for (std::map<std::string, std::string>::iterator it = lines.begin();
		it != lines.end(); ++it)
	{
		setAttribut(Config::nameAttributes.at(it->first), it->second);
	}
}
