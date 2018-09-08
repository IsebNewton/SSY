#pragma once
#include <SDL_ttf.h>
#include "GenericError.h"

class FontFactory
{
private:
	static bool isTTFInit;

public:
	static void initTTF();

	static TTF_Font* loadFont(const char* font, int size = 100);

	static void quit();
};

