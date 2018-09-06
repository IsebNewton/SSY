#pragma once
#include <SDL.h>

class Window
{
private:
	SDL_Window* window = nullptr;

public:
	Window();
	bool createWindow();
	void onRender();
	~Window();
};

