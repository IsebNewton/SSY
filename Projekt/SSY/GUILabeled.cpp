#include "GUILabeled.h"


GUILabeled::~GUILabeled()
{
	if (picture != NULL)
		SDL_DestroyTexture(picture);
	if (textTexture != NULL)
		SDL_DestroyTexture(textTexture);
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Getter/Setter										//
//////////////////////////////////////////////////////////////////////////////////////////

void GUILabeled::initialize()
{
	this->font = new Font("Arial", 11);
	this->backColor = SDL_Color{ 212, 212, 212 };
	this->foreColor = SDL_Color{ 0, 0, 0 };
}

void GUILabeled::setFont(Font * font)
{
	this->font = font;
	FontFactory::calculateTextSize(text, font->getFont(), &area.w, &area.h);
	// Astand der Schrift zum Rand
	area.w += 8;
	area.h += 8;
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
	FontFactory::calculateTextSize(text, font->getFont(), &area.w, &area.h);
	// Astand der Schrift zum Rand
	area.w += 8;
	area.h += 8;
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

		renderer->drawTexture(&pictureRect, picture);
	}

	renderer->drawText(this->text.c_str(), &this->textRect, this->font, this->foreColor);
	this->valid = true;
}
