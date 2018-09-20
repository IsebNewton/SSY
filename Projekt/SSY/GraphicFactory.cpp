#include "GraphicFactory.h"


bool GraphicFactory::isImageInit = false;

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
	std::string completePath = "../Bilder/" + std::string(path);
	SDL_Surface* picture = nullptr;

	picture = IMG_Load(completePath.c_str());
	if (picture == NULL)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, IMG_GetError());

	return picture;
}

// Lädt eine Texture
SDL_Texture * GraphicFactory::loadTexture(SDL_Renderer * renderer, const char * path)
{
	if (renderer == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer zum erstellen einer Textur darf nicht NULL sein.");

	SDL_Texture* texture = nullptr;
	SDL_Surface* picture = loadPicture(path);

	texture = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);	// Speicher wieder frei geben
	if (texture == nullptr)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, SDL_GetError());

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
	IMG_Quit();
}
