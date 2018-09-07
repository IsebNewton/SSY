#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"
#include <string>

class GraphicFactory
{
private:
	static bool isImageInit;
	static void initIMG();

public:
	static SDL_Surface* loadPicture(const char* path);
	static SDL_Texture* loadTexture(SDL_Renderer * renderer, const char* path);

	static void quit();
};

