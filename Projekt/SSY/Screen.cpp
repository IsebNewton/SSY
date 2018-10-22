#include "Screen.h"



Screen::Screen()
{ }

Screen::Screen(const char * menu)
{
	map = new Map(menu);
	map->createMap();
}

Screen::~Screen()
{
	for (std::map<std::string, Menu*>::iterator it = menus.begin(); it != menus.end(); ++it)
	{
		delete it->second;
	}
	menus.clear();
	for (std::list<ObjectControl*>::iterator it = objects.begin();
		it != objects.end(); ++it)
	{
		delete (*it);
	}
	objects.clear();
	if (background != NULL)
	{
		SDL_DestroyTexture(background);
	}
	if (map != NULL)
	{
		delete map;
	}
}

void Screen::addObject(ObjectControl * object)
{
	if (object != NULL && !(std::find(objects.begin(), objects.end(), object) != objects.end()))
	{
		this->objects.push_back(object);
	}
}

void Screen::addObjects(ObjectControl *object ...)
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

void Screen::removeObject(ObjectControl * object)
{
	if (object != NULL)
	{
		objects.remove_if([object](ObjectControl* value) { return (value == object); });
	}
}

void Screen::addMenu(std::string name, Menu * menu)
{
	if (menus.find(std::string(name)) == menus.end())
	{
		if (menu == NULL)
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Menü darf nicht NULL sein");
		else
		{
			menus.insert(std::pair<std::string, Menu*>(name, menu));

			std::list<GUIElement*> list = menu->getElements();
			for (std::list<GUIElement*>::iterator it = list.begin();
				it != list.end(); ++it)
			{
				this->addObject(*it);
			}
		}
	}
	else
	{
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Menü %s wurde schon in die Map eingefügt", name);
	}
}

void Screen::drawMap(Renderer * renderer)
{
	if (hasMap())
	{
		// TODO: Provisorisch die MiniMap positionieren
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 880;
		rect.w = 200;
		rect.h = 200;
		map->setMiniMapRect(rect);
		if (!map->isInitialized())
		{
			map->initTextures(renderer);
		}

		map->move();
		map->drawMap(renderer);
	}
}

void Screen::setBackground(SDL_Texture * background)
{
	this->background = background;
}

SDL_Texture * Screen::getBackground()
{
	return this->background;
}

std::list<ObjectControl*> Screen::getObjects()
{
	return this->objects;
}

Menu * Screen::getMenu(std::string name)
{
	return nullptr;
}

std::list<Menu*> Screen::getMenus()
{
	std::list<Menu*> list;
	for (std::map<std::string, Menu*>::iterator it = menus.begin(); it != menus.end(); ++it)
	{
		list.push_back(it->second);
	}
	return list;
}

bool Screen::hasMap()
{
	return map != nullptr;
}

Map * Screen::getMap()
{
	return map;
}
