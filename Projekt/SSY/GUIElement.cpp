#include "GUIElement.h"

//////////////////////////////////////////////////////////////////////////////////////////
//									Getter/Setter										//
//////////////////////////////////////////////////////////////////////////////////////////

void GUIElement::setBackColor(SDL_Color color)
{
	this->backColor = color;
	this->invalidate();
}

void GUIElement::setForeColor(SDL_Color color)
{
	this->foreColor = color;
	this->invalidate();
}

SDL_Color GUIElement::getBackColor()
{
	return this->backColor;
}

SDL_Color GUIElement::getForeColor()
{
	return this->foreColor;
}
