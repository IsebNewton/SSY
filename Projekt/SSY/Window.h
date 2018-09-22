#pragma once
#include <SDL.h>
#include <list>
#include <algorithm>
#include "ObjectControl.h"
#include "GenericError.h"
#include "Renderer.h"

class Window
{
private:
	std::list<ObjectControl*> objects;

	SDL_Window * window = nullptr;
	Renderer * renderer = nullptr;
	SDL_Texture* background = nullptr;

public:
	Window();
	bool createWindow();
	void onRender();
	SDL_Window* getWindow();

	void addObject(ObjectControl* object);
	void removeObject(ObjectControl* object);

	~Window();
};

