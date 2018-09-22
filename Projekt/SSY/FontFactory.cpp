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

	// Schlüssel muss auch Größe speichern damit unterschiedliche Größen geladen werden können
	std::string key = std::string(font) + ", " + std::to_string(size);
	if (fonts.find(std::string(key)) == fonts.end())
	{
		std::string fontPath = "C:\\Windows\\Fonts\\" + std::string(font) + ".ttf";

		retFont = TTF_OpenFont(fontPath.c_str(), size);
		if (retFont == NULL)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, TTF_GetError());
		}
		fonts.insert(std::pair<std::string, TTF_Font*>(key, retFont));
	}
	else
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Schrift %s in der Größe %d wurde schon geladen.", font, size);
	}
	
	return retFont;
}

TTF_Font * FontFactory::getFont(const char * font, int size)
{
	TTF_Font * retFont = NULL;

	std::string key = std::string(font) + ", " + std::to_string(size);
	if (fonts.find(std::string(key)) != fonts.end())
	{
		retFont = fonts.at(std::string(key));
	}
	else
	{
		retFont = loadFont(font, size);
	}

	return retFont;
}

void FontFactory::calculateTextSize(std::string text, TTF_Font * font, int * width, int * height)
{
	if (font == NULL)
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Schrift zum Kalkulieren darf nicht NULL sein.");
	else
	{
		SDL_Surface * surface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color{ 0, 0, 0 });
		*width = surface->w;
		*height = surface->h;

		SDL_FreeSurface(surface);
	}
}

void FontFactory::quit()
{
	for (std::map<std::string, TTF_Font*>::iterator it = fonts.begin(); it != fonts.end(); ++it)
	{
		TTF_CloseFont(it->second);
	}

	TTF_Quit();
}
