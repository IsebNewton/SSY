#pragma once
#include <SDL.h>
#include <list>
#include <algorithm>
#include "Menu.h"
#include "Button.h"
#include "ObjectControl.h"
#include "GenericError.h"
#include "Renderer.h"
#include "Screen.h"

class Window
{
private:
	Screen* screen = nullptr;

	SDL_Window * window = nullptr;
	Renderer * renderer = nullptr;

	void initWindow();

public:
	Window();
	bool createWindow();
	void onRender();

	Screen* getScreen();
	SDL_Window* getWindow();

	~Window();
};

