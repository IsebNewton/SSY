#include "ObjectControl.h"



ObjectControl::ObjectControl()
	: ObjectControl(0, 0, 0, 0)
{ }

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
	this->invalidate();
}

void ObjectControl::setY(int posY)
{
	this->area.y = posY;
	this->invalidate();
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

	onResize();
	this->invalidate();
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

	onResize();
	this->invalidate();
}

void ObjectControl::setVisible(bool visible)
{
	this->visible = visible;
	this->invalidate();
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
	int mouseX = InputWrapper::getMouseX();
	int mouseY = InputWrapper::getMouseY();

	if ((mouseX >= this->area.x) && (mouseX < (this->area.x + this->area.w))
		&& (mouseY > this->area.y) && (mouseY < (this->area.y + this->area.h)))
	{
		this->state.hovered = true;
		this->state.pressed = false;
		if (InputWrapper::isMouseButtonDownNow(SDL_BUTTON_LEFT))
		{
			this->state.clicked = true;
		}
		if (InputWrapper::isMouseButtonUpNow(SDL_BUTTON_LEFT))
		{
			this->state.pressed = true;
			this->state.clicked = false;
		}
	}
	else
	{
		this->state.clicked = false;
		this->state.pressed = false;
		this->state.hovered = false;
	}

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
