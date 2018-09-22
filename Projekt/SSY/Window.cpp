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
		1024, 768, SDL_WINDOW_RESIZABLE);
	
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

void Window::addObject(ObjectControl * object)
{
	if (object != NULL && (std::find(objects.begin(), objects.end(), object) != objects.end()))
	{
		this->objects.push_back(object);
	}
}

void Window::removeObject(ObjectControl * object)
{
	if (object != NULL)
	{
		objects.remove_if([object](ObjectControl* value) { return (value == object); });
	}
}

Window::~Window()
{
	delete renderer;
	SDL_DestroyTexture(background);
	SDL_DestroyWindow(window);
}
