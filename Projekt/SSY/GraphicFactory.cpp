#include "GraphicFactory.h"


bool GraphicFactory::isImageInit = false;

// Initialisiert Bibliothek wenn sie noch nicht initialisiert wurde
void GraphicFactory::initIMG()
{
	if (!isImageInit)
	{
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			throw SDLImageError();
		if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
			throw SDLImageError();

		isImageInit = true;
	}
}

//Lädt ein Bild
SDL_Surface * GraphicFactory::loadPicture(const char * path)
{
	initIMG();

	std::string completePath = "../Bilder/" + std::string(path);
	SDL_Surface* picture = nullptr;

	picture = IMG_Load(completePath.c_str());
	if (picture == NULL)
		throw SDLImageError();

	return picture;
}

// Lädt eine Texture
SDL_Texture * GraphicFactory::loadTexture(SDL_Renderer * renderer, const char * path)
{
	if (renderer == nullptr)
		throw GraphicHelperError("Renderer darf nicht null sein");

	initIMG();

	SDL_Texture* texture = nullptr;
	SDL_Surface* picture = loadPicture(path);

	texture = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);	// Speicher wieder frei geben
	if (texture == nullptr)
		throw GraphicHelperError();

	return texture;
}

void GraphicFactory::quit()
{
	IMG_Quit();
}
