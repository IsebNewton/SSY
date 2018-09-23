#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>
#include "GenericError.h"

class GraphicFactory
{
private:
	static bool isImageInit;
	static std::map<std::string, SDL_Texture*> textures;
	static std::map<std::string, SDL_Surface*> surfaces;

public:
	static void initIMG();

	/**
	Läd ein Bild aus dem Bilder Ordner.

	@param path Pfad zum Bild.

	@return Geladenes Bild oder NULL, wenn das Bild schon geladen wurde.
	*/
	static SDL_Surface* loadPicture(const char* path);

	/**
	Sucht eine geladenes Bild.

	@param path Pfad zum Bild.

	@return Das gesuchte Bild.
	*/
	static SDL_Surface* getPicture(const char* path);

	/**
	Sucht eine geladene Textur.

	@param path Pfad zum Bild welches als Textur geladen werden soll.

	@return geladene Textur.
	*/
	static SDL_Texture* getTexture(SDL_Renderer * renderer, const char* path);

	/**
	Läd eine Textur von dem übergebenen Bild.

	@param path Pfad zum Bild, von welchem die Textur geladen werden soll.

	@return geladene Textur oder NULL, wenn die Texture schon geladen wurde.
	*/
	static SDL_Texture* loadTexture(SDL_Renderer * renderer, const char* path);

	/**
	Läd eine Textur von dem übergebenen Bild.

	@param path Pfad zum Bild, von welchem die Textur geladen werden soll.

	@return geladene Textur oder NULL, wenn ein Fehler aufgetreten ist.
	*/
	static SDL_Texture* loadTextureFromSurface(SDL_Renderer * renderer, SDL_Surface* surface);

	static void quit();
};

