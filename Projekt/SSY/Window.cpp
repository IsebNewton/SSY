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
	// Hintergrund zeichnen
	if (screen->getBackground() != NULL)
	{
		renderer->drawBackground(screen->getBackground());
	}
	else
	{
		renderer->drawBackground(Color::WHITE);
	}

	// Menüs rendern
	std::list<Menu*> menuList = screen->getMenus();
	for (std::list<Menu*>::iterator it = menuList.begin();
		it != menuList.end(); ++it)
	{
		if ((*it)->isVisible())
		{
			(*it)->onPaint(renderer);
		}
	}

	std::list<ObjectControl*> objectList = screen->getObjects();
	for (std::list<ObjectControl*>::iterator it = objectList.begin();
		it != objectList.end(); ++it)
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
	screen = new Screen();
	screen->setBackground(renderer->getTexture("StartWallpaper.jpg"));

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

	menu->addElements(startButton, optButton, exitButton, NULL);
	screen->addMenu("Hauptmenü", menu);
}

Screen * Window::getScreen()
{
	return screen;
}

SDL_Window* Window::getWindow()
{
	return window;
}

Window::~Window()
{
	delete screen;
	delete renderer;
	SDL_DestroyWindow(window);
}
