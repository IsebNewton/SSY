#include "Window.h"
#include "Core.h"
#include "Color.h"

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
		0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	
	if (window == nullptr)
	{
		ret = false;
	}
	renderer = new Renderer(window);

	initWindow();

	return ret;
}

void Window::onRender()
{
	renderer->drawBackground(background);
	if (activeMenu != NULL && activeMenu->isVisible())
		activeMenu->onPaint(renderer);

	for (std::list<ObjectControl*>::iterator it = this->objects.begin();
		it != this->objects.end(); ++it)
	{
		if ((*it)->isVisible())
		{
			(*it)->onPaint(renderer);
		}
	}

	renderer->presentRenderer();
}

void Window::initWindow()
{
	if (background == NULL)
	{
		background = renderer->getTexture("StartWallpaper.jpg");
	}

	// TODO: Menü seperat erstellen und hier nur setzen
	int width = 0;
	int height = 0;
	SDL_GetWindowSize(window, &width, &height);

	Menu* menu = new Menu();
	menu->setHeight(height / 2);
	menu->setWidth(width / 3);
	menu->setX(width / 3);
	menu->setY(height / 5 * 2);
	menu->setCaption("Age of Kacke");

	int buttonWidth = menu->getWidth() / 5 * 3;
	int buttonHeight = menu->getHeight() / 9;

	Font* captionFont = new Font("ITCBLKAD", 64);
	captionFont->setStyle(TTF_STYLE_ITALIC);
	menu->getCaptionLabel()->setFont(captionFont);
	menu->getCaptionLabel()->setForeColor(Color::MAROON);


	Font* font = new Font("ITCBLKAD", 32);

	Button* startButton = new Button("Single Player");
	startButton->setWidth(buttonWidth);
	startButton->setHeight(buttonHeight);
	startButton->setX(menu->getWidth() / 5);
	startButton->setY(menu->getHeight() / 9 * 2);
	startButton->setFont(font);

	Button* optButton = new Button("Options");
	optButton->setWidth(buttonWidth);
	optButton->setHeight(buttonHeight);
	optButton->setX(menu->getWidth() / 5);
	optButton->setY(menu->getHeight() / 9 * 3 + 24);
	optButton->setFont(font);

	Button* exitButton = new Button("Exit");
	exitButton->setWidth(buttonWidth);
	exitButton->setHeight(buttonHeight);
	exitButton->setX(menu->getWidth() / 5);
	exitButton->setY(menu->getHeight() / 9 * 4 + 2 * 24);
	exitButton->setFont(font);
	exitButton->setOnAction([](void*) -> int {
		Core::quit = true;
		return 0;
	});

	menu->addObjects(startButton, optButton, exitButton, NULL);
	this->setMenu(menu);
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
	va_start(objects, object);

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
