#include "ObjectControl.h"



ObjectControl::ObjectControl(SDL_Rect area)
	: ObjectControl(area.x, area.y, area.w, area.h)
{ }

ObjectControl::ObjectControl(int width, int height)
	: ObjectControl(0, 0 , width, height)
{ }

ObjectControl::ObjectControl(int posX, int posY, int width, int height)
{
	this->area.x = posX;
	this->area.y = posY;
	this->setWidth(width);
	this->setHeight(height);

	this->visible = true;
	this->valid = false;
}

ObjectControl::~ObjectControl()
{
	// TODO:
}

void ObjectControl::invalidate()
{
	this->valid = false;
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Getter/Setter										//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//										Setter											//
//////////////////////////////////////////////////////////////////////////////////////////

void ObjectControl::setX(int posX)
{
	this->area.x = posX;
}

void ObjectControl::setY(int posY)
{
	this->area.y = posY;
}

void ObjectControl::setWidth(int width)
{
	if (width < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Breite darf nicht negativ sein.");
		this->area.w = 0;
	}
	else
		this->area.w = width;
}

void ObjectControl::setHeight(int height)
{
	if (height < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Höhe darf nicht negativ sein.");
		this->area.h = 0;
	}
	else
		this->area.h = height;
}

void ObjectControl::setState(State state)
{
	this->state = state;
}

void ObjectControl::setVisible(bool visible)
{
	this->visible = visible;
}

void ObjectControl::setOnAction(void(*function)(void))
{
	this->onAction = function;
}

//////////////////////////////////////////////////////////////////////////////////////////
//										Getter											//
//////////////////////////////////////////////////////////////////////////////////////////

int ObjectControl::getX()
{
	return this->area.x;
}

int ObjectControl::getY()
{
	return this->area.y;
}

int ObjectControl::getWidth()
{
	return this->area.w;
}

int ObjectControl::getHeight()
{
	return this->area.h;
}

State ObjectControl::getState()
{
	return this->state;
}

bool ObjectControl::isVisible()
{
	return this->visible;
}

bool ObjectControl::isValid()
{
	return this->valid;
}
