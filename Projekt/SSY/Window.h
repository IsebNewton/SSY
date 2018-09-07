#pragma once
#include <SDL.h>
#include "GenericError.h"
#include "Renderer.h"

class Window
{
private:
	SDL_Window * window = nullptr;
	Renderer * renderer = nullptr;
	SDL_Surface* background = nullptr;

public:
	Window();
	bool createWindow();
	void onRender();
	SDL_Window* getWindow();
	~Window();
};

