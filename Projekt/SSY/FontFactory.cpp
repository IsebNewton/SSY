#include "FontFactory.h"

bool FontFactory::isTTFInit = false;

void FontFactory::initTTF()
{
	if (!isTTFInit)
	{
		if (TTF_Init() != 0)
		{
			throw GenericError("SDL_TTF: TTF konnte nicht initialisiert werden");
		}
		isTTFInit = true;
	}
}

TTF_Font * FontFactory::loadFont(const char * font, int size)
{
	std::string fontPath = "C:\\Windows\\Fonts\\" + std::string(font) + ".ttf";

	TTF_Font * retFont = TTF_OpenFont(fontPath.c_str(), size);
	if (retFont == NULL)
		throw GenericError("SDL_TTF: Schrift konnte nicht geladen werden");

	return retFont;
}

void FontFactory::quit()
{
	TTF_Quit();
}
