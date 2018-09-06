#pragma once
#include <SDL.h>
#include "GenericError.h"

class Window
{
private:
	SDL_Window* window = nullptr;

public:
	Window();
	bool createWindow();
	void onRender();
	SDL_Window* getWindow();
	~Window();
};

