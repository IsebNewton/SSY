#include "Window.h"
#include "Core.h"

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

	initWindow();

	return ret;
}

void Window::onRender()
{
	renderer->drawBackground(background);
	if (activeMenu != NULL)
		activeMenu->onPaint(renderer);

	for (std::list<ObjectControl*>::iterator it = this->objects.begin();
		it != this->objects.end(); ++it)
	{
		(*it)->onPaint(renderer);
	}

	renderer->presentRenderer();
}

void Window::initWindow()
{
	// TODO: Menü nur einmal zentral erstellen
}

SDL_Window* Window::getWindow()
{
	return window;
}

void Window::addObject(ObjectControl * object)
{
	if (object != NULL && !(std::find(objects.begin(), objects.end(), object) != objects.end()))
	{
		this->objects.push_back(object);
	}
}

void Window::addObjects(ObjectControl *object ...)
{
	ObjectControl* control = object;

	va_list objects;
	va_start(objects, control);

	while (control != NULL)
	{
		this->addObject(control);
		control = va_arg(objects, ObjectControl*);
	}

	va_end(objects);
}

void Window::removeObject(ObjectControl * object)
{
	if (object != NULL)
	{
		objects.remove_if([object](ObjectControl* value) { return (value == object); });
	}
}

void Window::setMenu(Menu * menu)
{
	if (activeMenu != menu)
	{
		delete activeMenu; // Speicher wieder freigeben wenn es nicht das gleiche Menü ist

		if (menu != NULL)
		{
			std::list<GUIElement*> list = menu->getObjects();
			for (std::list<GUIElement*>::iterator it = list.begin();
				it != list.end(); ++it)
			{
				this->addObject(*it);
			}
		}
	}
	this->activeMenu = menu;
}

std::list<ObjectControl*> Window::getObjects()
{
	return this->objects;
}

Menu * Window::getMenu()
{
	return this->activeMenu;
}

Window::~Window()
{
	if (activeMenu != NULL)
	{
		delete activeMenu;
	}
	objects.clear();
	delete renderer;
	SDL_DestroyTexture(background);
	SDL_DestroyWindow(window);
}
