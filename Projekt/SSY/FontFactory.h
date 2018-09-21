#pragma once
#include <SDL_ttf.h>
#include <map>
#include "GenericError.h"

class FontFactory
{
private:
	static bool isTTFInit;
	static std::map<std::string, TTF_Font*> fonts;

public:
	static void initTTF();

	/**
	L�dt eine Schrift mit der angegebenen Gr��e.

	@param font zu ladende Schrift.
	@param size Schriftgr��e (Je h�her diese ist desto detailierter ist diese).

	@return Die gesuchte Schrift oder NULL, wenn die Schrift noch nicht geladen wurde.
	*/
	static TTF_Font* loadFont(const char* font, int size = 11);

	/**
	Sucht eine geladene Schrift.

	@param font suchende Schrift.

	@return Die gesuchte Schrift oder NULL, wenn die Schrift noch nicht geladen wurde.
	*/
	static TTF_Font* getFont(const char* font, int size = 11);

	static void quit();
};

