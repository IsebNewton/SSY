#include "GUILabeled.h"
#include "Color.h"

GUILabeled::~GUILabeled()
{
	if (picture != NULL)
		SDL_DestroyTexture(picture);
}

void GUILabeled::updateSize()
{
	int width = 0;
	int height = 0;
	FontFactory::calculateTextSize(text, font->getFont(), &width, &height);
	if (width >= area.w)
	{
		area.w = width + 8;	// Astand der Schrift zum Rand
	}
	if (height >= area.h)
	{
		area.h = height + 8;	// Astand der Schrift zum Rand
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Getter/Setter										//
//////////////////////////////////////////////////////////////////////////////////////////

void GUILabeled::initialize()
{
	this->font = new Font("Arial", 11);
	this->foreColor = Color::BLACK;
}

void GUILabeled::setFont(Font * font)
{
	this->font = font;
	this->updateSize();
	this->invalidate();
}

void GUILabeled::setPicture(SDL_Texture * picture)
{
	this->picture = picture;
	this->invalidate();
}

void GUILabeled::setText(std::string text)
{
	this->text = text;
	this->updateSize();
	this->invalidate();
}

Font * GUILabeled::getFont()
{
	return this->font;
}

SDL_Texture * GUILabeled::getPicture()
{
	return this->picture;
}

std::string GUILabeled::getText()
{
	return this->text;
}

void GUILabeled::onPaint(Renderer * renderer)
{
	this->textRect = this->area;

	if (picture != NULL)
	{
		// Bild soll immer quadratisch sein
		SDL_Rect pictureRect = SDL_Rect{this->area.x, this->area.y, this->area.h, this->area.h};
		this->textRect.x = this->area.x + pictureRect.w + 4;
		this->textRect.w = pictureRect.w - 4;

		renderer->drawTexture(&pictureRect, picture, this->foreColor.a);
	}

	renderer->drawText(this->text.c_str(), &this->textRect, this->font, this->foreColor);
	this->valid = true;
}
