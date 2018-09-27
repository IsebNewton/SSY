#include "Button.h"
#include "Color.h"

Button::~Button()
{
}

void Button::initialize()
{
	GUILabeled::initialize();

	this->borderSize = 2;
	area.w += 2 * borderSize;
	area.h += 2 * borderSize;
	this->foreColor = Color::BLACK;
	this->backColor = Color::fromARGB(140, 97, 6, 128);
	this->borderColor = Color::fromRGB(134, 61, 10);
	this->hoveredColor = Color::fromARGB(247, 190, 74, 128);
	this->clickedColor = Color::fromARGB(134, 61, 10, 64);
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Getter/Setter										//
//////////////////////////////////////////////////////////////////////////////////////////

void Button::setBorder(int borderSize)
{
	if (borderSize < 0)
		borderSize = 0;
	this->borderSize = borderSize;
}

void Button::setBorderColor(SDL_Color borderColor)
{
	this->borderColor = borderColor;
}

void Button::setHoveredColor(SDL_Color hoveredColor)
{
	this->hoveredColor = hoveredColor;
}

void Button::setClickedColor(SDL_Color clickedColor)
{
	this->clickedColor = clickedColor;
}

int Button::getBorder()
{
	return this->borderSize;
}

SDL_Color Button::getBorderColor()
{
	return this->backColor;
}

SDL_Color Button::getHoveredColor()
{
	return this->hoveredColor;
}

SDL_Color Button::getClickedColor()
{
	return this->clickedColor;
}

void Button::onPaint(Renderer * renderer)
{
	SDL_Rect clientRect = SDL_Rect{ this->area.x + borderSize, this->area.y + borderSize,
		this->area.w - 2 * borderSize, this->area.h - 2 * borderSize };
	if (this->getState().hovered)
	{
		if (this->getState().clicked)
		{
			renderer->drawBackground(&clientRect, clickedColor);
		}
		else
		{
			renderer->drawBackground(&clientRect, hoveredColor);
		}
	}
	else
	{
		renderer->drawBackground(&clientRect, backColor);
	}
	renderer->drawRectangle(&area, borderSize, borderColor),

	GUILabeled::onPaint(renderer);
}
