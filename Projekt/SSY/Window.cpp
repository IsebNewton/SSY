#include "Window.h"



Window::Window()
{
}

/*
Startet ein einfaches Fenster
*/
bool Window::createWindow()
{
	bool ret = true;
	// Öffnet das Fenster in der Mitte des Bildschirmes
	window = SDL_CreateWindow("Age of Kacke", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		400, 400, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		ret = false;
	}

	return ret;
}

void Window::onRender()
{
	// TODO: Alle Controls im Window rendern
}


Window::~Window()
{
	SDL_DestroyWindow(window);
}
