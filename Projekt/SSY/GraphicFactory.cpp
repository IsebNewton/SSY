#include "GraphicFactory.h"


bool GraphicFactory::isImageInit = false;
std::map<std::string, SDL_Texture*> GraphicFactory::textures;
std::map<std::string, SDL_Surface*> GraphicFactory::surfaces;

// Initialisiert Bibliothek wenn sie noch nicht initialisiert wurde
void GraphicFactory::initIMG()
{
	if (!isImageInit)
	{
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			throw IMGError();
		if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
			throw IMGError();

		isImageInit = true;
	}
}

//Lädt ein Bild
SDL_Surface * GraphicFactory::loadPicture(const char * path)
{
	SDL_Surface* picture = NULL;
	std::string key = std::string(path);
	if (surfaces.find(std::string(key)) == surfaces.end())
	{
		std::string completePath = "../Bilder/" + std::string(path);

		picture = IMG_Load(completePath.c_str());
		if (picture == NULL)
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, IMG_GetError());
	}
	else
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Bild %s wurde schon geladen.", path);
	}

	return picture;
}

SDL_Surface * GraphicFactory::getPicture(const char * path)
{
	SDL_Surface * picture = NULL;

	std::string key = std::string(path);
	if (surfaces.find(std::string(key)) != surfaces.end())
	{
		picture = surfaces.at(std::string(key));
	}
	else
	{
		picture = loadPicture(path);
	}

	return picture;
}

SDL_Texture * GraphicFactory::getTexture(SDL_Renderer * renderer, const char * path)
{
	SDL_Texture * texture = NULL;

	std::string key = std::string(path);
	if (textures.find(std::string(key)) != textures.end())
	{
		texture = textures.at(std::string(key));
	}
	else
	{
		texture = loadTexture(renderer, path);
	}

	return texture;
}

// Lädt eine Texture
SDL_Texture * GraphicFactory::loadTexture(SDL_Renderer * renderer, const char * path)
{
	SDL_Texture* texture = NULL;

	if (renderer == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer zum erstellen einer Textur darf nicht NULL sein.");
	else
	{

		std::string key = std::string(path);
		if (textures.find(std::string(key)) == textures.end())
		{
			SDL_Surface* picture = loadPicture(path);
			texture = SDL_CreateTextureFromSurface(renderer, picture);
			SDL_FreeSurface(picture);	// Speicher wieder frei geben
			picture = NULL;

			if (texture == nullptr)
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());
			else
				textures.insert(std::pair<std::string, SDL_Texture*>(key, texture));
		}
		else
		{
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Textur %s wurde schon geladen.", path);
		}
	}

	return texture;
}

SDL_Texture * GraphicFactory::loadTextureFromSurface(SDL_Renderer * renderer, SDL_Surface * surface)
{
	if(renderer == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer zum erstellen einer Textur darf nicht NULL sein.");
	if (surface == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Bild zum erstellen einer Textur darf nicht NULL sein..");

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());

	return texture;
}

void GraphicFactory::quit()
{
	for (std::map<std::string, SDL_Surface*>::iterator it = surfaces.begin(); it != surfaces.end(); ++it)
	{
		SDL_FreeSurface(it->second);
		it->second = NULL;
	}
	for (std::map<std::string, SDL_Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		SDL_DestroyTexture(it->second);
	}

	IMG_Quit();
}
