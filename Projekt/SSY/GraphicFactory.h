#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "GenericError.h"

class GraphicFactory
{
private:
	static bool isImageInit;

public:
	static void initIMG();

	static SDL_Surface* loadPicture(const char* path);
	static SDL_Texture* loadTexture(SDL_Renderer * renderer, const char* path);
	static SDL_Texture* loadTextureFromSurface(SDL_Renderer * renderer, SDL_Surface* surface);

	static void quit();
};

