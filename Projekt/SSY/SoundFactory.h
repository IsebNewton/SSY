#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <map>

class SoundFactory
{
private:
	static std::map<std::string, Mix_Music*> musicData;
	static std::map<std::string, Mix_Chunk*> chunkData;

	static int musicVolume;
	static int soundVolume;

public:
	static void initAUDIO();

	/**
	Spielt eine gegebene Musik ab.

	@param path Datei.
	@param loops Gibt an, wie oft der Sound wiederholt werden soll.
		-1 => Unendlich
	*/
	static void playMusic(const char* file, int loops = 0);

	/**
	Gibt an ob gerade eine Musik am laufen ist.

	@return true wenn gerade Musik l�uft und false wenn nicht
	*/
	static bool isMusicPlaying();

	/**
	Setzt die Lautst�rke der Musik.

	@param volume Lautst�rke.
	*/
	static void setMusicVolume(int volume);

	/**
	Gibt die Lautst�rke der Musik zur�ck.

	@return Lautst�rke
	*/
	static int getMusicVolume();

	/**
	Pausiert die aktuell laufende Musik.
	*/
	static void pauseMusic();

	/**
	Spielt die pausierte Musik weiter.
	*/
	static void resumeMusic();

	/**
	Spielt den gegebenen Sound ab. (Muss eine .wav-Datei sein)

	@param path Datei.
	@param loops Gibt an, wie oft der Sound wiederholt werden soll.
		-1 => Unendlich
	*/
	static void playSound(const char* file, int loops = 0);

	/**
	Spielt den gegebenen Sound ab. (Muss eine .wav-Datei sein)

	@param path Datei.
	@param channel Gibt an, auf welchem Channel der Sound gespielt werden soll.
	@param loops Gibt an, wie oft der Sound wiederholt werden soll.
			-1 => Unendlich
	*/
	static void playSound(const char* file, int channel, int loops = 0);

	/**
	Setzt die Lautst�rke der Sounds, bzw. eines einzelnen Channels.

	@param volume Lautst�rke.
	@param channel Channel, auf welchem die Lautst�rke gestzt werden soll.
	*/
	static void setSoundVolume(int volume, int channel = -1);

	/**
	Gibt die Lautst�rke der Sounds zur�ck. (von allen Channel)

	@return Lautst�rke
	*/
	static int getSoundVolume();

	/**
	Pausiert den Sound auf dem gegebenen Channel

	@param channel Channel, welcher angehalten werden soll. (-1 f�r alle)
	*/
	static void pauseSound(int channel = -1);

	/**
	Einen angehaltenen Channel weiter spielen.

	@param channel Channel, welcher angehalten werden soll. (-1 f�r alle)
	*/
	static void resumeSound(int channel = -1);

	/**
	Gibt an ob gerade ein Sound am laufen ist.

	@return true wenn gerade Sound l�uft und false wenn nicht
	*/
	static bool isSoundPlaying(int channel = -1);

	/**
	Setzt eine Anzahl an Channel auf denen ein Sound abgespielt werden kann.

	@param channels Anzahl an channel.
	*/
	static void setChannel(int channels);

	static void quit();
};

