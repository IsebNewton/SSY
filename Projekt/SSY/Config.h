#pragma once
#include <string>
#include <map>
#include <SDL.h>
#include <exception>

class Config
{
public:
	static enum class ConfigAttributes
	{
		FULLSCREEN,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,

		MUSIC_ON,
		SOUND_ON,
		MUSIC_VOLUME,
		SOUND_VOLUME
	};

	static std::map<ConfigAttributes, std::string> attributeNames;
	static std::map<std::string, ConfigAttributes> nameAttributes;

private:
	static void setAttribut(Config::ConfigAttributes attribut, std::string value);

public:
	// Fenstereinstellungen					Einträge in der Datei:
	static bool fullscreen;					// Fullscreen

	static int windowWidth;					// Windowwidth
	static int windowHeight;				// Windowheight

	// Sound und Musik-Einstellungen
	static bool musicOn;					// Music
	static bool soundOn;					// Sound

	static int musicVolume;					// Musicvolume
	static int soundVolume;					// Soundvolume

	/**
	Speichert alle Daten in die config/config.txt
	*/
	static void save();
	
	/**
	Liest aus der config/config.txt alle Einstellungen aus und setzt
	die Attribute dementsprechend.
	*/
	static void readConfig();
};
