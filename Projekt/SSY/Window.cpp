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
	// �ffnet das Fenster in der Mitte des Bildschirmes
	window = SDL_CreateWindow("Age of Kacke", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1024, 768, SDL_WINDOW_SHOWN);
	
	if (window == nullptr)
	{
		ret = false;
	}
	renderer = new Renderer(window);

	if (background == NULL)
	{
		background = renderer->getTexture("Testscreen.bmp");
	}

	return ret;
}

void Window::onRender()
{
	renderer->drawBackground(background);
	
	renderer->presentRenderer();
}

SDL_Window* Window::getWindow()
{
	return window;
}

Window::~Window()
{
	SDL_DestroyTexture(background);
	SDL_DestroyWindow(window);
}