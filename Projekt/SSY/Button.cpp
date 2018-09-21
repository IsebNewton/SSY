#include "Button.h"


Button::~Button()
{
}

void Button::initialize()
{
	GUILabeled::initialize();

	this->borderSize = 3;
	this->borderColor = SDL_Color{78, 61, 49, 255};
	this->foreColor = SDL_Color{ 255, 255, 0, 255 };
	this->hoveredColor = SDL_Color{ 96, 69, 57, 255 };
	this->clickedColor = SDL_Color{ 104, 77, 65, 255 };
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
