#include "GUIElement.h"

//////////////////////////////////////////////////////////////////////////////////////////
//									Getter/Setter										//
//////////////////////////////////////////////////////////////////////////////////////////

void GUIElement::setForeColor(SDL_Color color)
{
	this->foreColor = color;
	this->invalidate();
}

SDL_Color GUIElement::getForeColor()
{
	return this->foreColor;
}
