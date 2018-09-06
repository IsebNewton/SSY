#pragma once
#include <SDL.h>
#include "Window.h"
#include <string>

class Surface
{
private:
	SDL_Surface *surface_window = nullptr;
	Window *window;
public:
	Surface(Window *window);
	~Surface();
	void laden(const char* name);
	void aktualisieren();
};

