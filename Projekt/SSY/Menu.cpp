#include "Menu.h"



Menu::Menu()
	: Menu(1024, 768)	// TODO: Menü über das ganze Fenster strecken
{ }

Menu::Menu(SDL_Rect area)
	: Menu(area.x, area.y, area.w, area.h)
{ }

Menu::Menu(int width, int height)
	: Menu(0, 0, width, height)
{ }

Menu::Menu(int posX, int posY, int width, int height)
{
	this->area.x = posX;
	this->area.y = posY;
	this->setWidth(width);
	this->setHeight(height);
}


Menu::~Menu()
{
}

void Menu::invalidate()
{
	this->valid = false;
}

void Menu::addObject(GUIElement * object)
{
	if (object != NULL && !(std::find(objects.begin(), objects.end(), object) != objects.end()))
	{
		object->setX(object->getX() + this->getX());
		object->setY(object->getY() + this->getY());
		this->objects.push_back(object);
	}
}

void Menu::removeObject(GUIElement * object)
{
	if (object != NULL)
	{
		objects.remove_if([object](GUIElement* value) { return (value == object); });
	}
}

void Menu::onPaint(Renderer* renderer)
{
	for (std::list<GUIElement*>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		(*it)->onPaint(renderer);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Getter/Setter										//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//										Setter											//
//////////////////////////////////////////////////////////////////////////////////////////

void Menu::setX(int posX)
{
	this->area.x = posX;
	this->invalidate();
}

void Menu::setY(int posY)
{
	this->area.y = posY;
	this->invalidate();
}

void Menu::setWidth(int width)
{
	if (width < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Breite darf nicht negativ sein.");
		this->area.w = 0;
	}
	else
		this->area.w = width;

	this->invalidate();
}

void Menu::setHeight(int height)
{
	if (height < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Höhe darf nicht negativ sein.");
		this->area.h = 0;
	}
	else
		this->area.h = height;

	this->invalidate();
}

void Menu::setVisible(bool visible)
{
	this->visible = visible;
	this->invalidate();
}

//////////////////////////////////////////////////////////////////////////////////////////
//										Getter											//
//////////////////////////////////////////////////////////////////////////////////////////

int Menu::getX()
{
	return this->area.x;
}

int Menu::getY()
{
	return this->area.y;
}

int Menu::getWidth()
{
	return this->area.w;
}

int Menu::getHeight()
{
	return this->area.h;
}

bool Menu::isVisible()
{
	return this->visible;
}

bool Menu::isValid()
{
	return this->valid;
}

std::list<GUIElement*> Menu::getObjects()
{
	return objects;
}
