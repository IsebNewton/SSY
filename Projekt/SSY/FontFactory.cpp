#include "FontFactory.h"

bool FontFactory::isTTFInit = false;
std::map<std::string, TTF_Font*> FontFactory::fonts;

void FontFactory::initTTF()
{
	if (!isTTFInit)
	{
		if (TTF_Init() != 0)
		{
			throw TTFError();
		}
		isTTFInit = true;
	}
}

TTF_Font * FontFactory::loadFont(const char * font, int size)
{
	TTF_Font * retFont = NULL;	
	if (fonts.find(std::string(font)) == fonts.end())
	{
		std::string fontPath = "C:\\Windows\\Fonts\\" + std::string(font) + ".ttf";

		retFont = TTF_OpenFont(fontPath.c_str(), size);
		if (retFont == NULL)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, TTF_GetError());
		}
		fonts.insert(std::pair<std::string, TTF_Font*>(std::string(font), retFont));
	}
	else
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Schrift %s wurde schon geladen.", font);
	}
	
	return retFont;
}

TTF_Font * FontFactory::getFont(const char * font)
{
	TTF_Font * retFont = NULL;
	if (fonts.find(std::string(font)) != fonts.end())
	{
		retFont = fonts.at(std::string(font));
	}
	else
	{
		retFont = loadFont(font);
	}

	return retFont;
}

void FontFactory::quit()
{
	for (std::map<std::string, TTF_Font*>::iterator it = fonts.begin(); it != fonts.end(); ++it)
	{
		TTF_CloseFont(it->second);
	}

	TTF_Quit();
}
