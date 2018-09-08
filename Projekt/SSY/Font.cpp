#include "Font.h"



Font::Font(const char * font = "Arial")
{
	this->fontName = font;
	this->size = 24;
	this->font = FontFactory::loadFont(font);
}

Font::Font(const char * font, SDL_Color color, int size)
{
	this->fontName = font;
	this->size = size;
	this->font = FontFactory::loadFont(font);
}

Font::Font(const char * font, SDL_Color color, int size, int style)
{
	this->fontName = font;
	this->size = size;
	this->font = FontFactory::loadFont(font);
	this->setStyle(style);
}

Font::~Font()
{
	TTF_CloseFont(font);
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Getter/Setter										//
//////////////////////////////////////////////////////////////////////////////////////////

TTF_Font * Font::getFont()
{
	return this->font;
}

void Font::setFont(TTF_Font * font)
{
	if (font != NULL)
		this->font = font;
}

SDL_Color Font::getColor()
{
	return this->color;
}

void Font::setColor(SDL_Color color)
{
	this->color = color;
}

int Font::getSize()
{
	return this->size;
}

void Font::setSize(int size)
{
	if (size < 0)
		SDL_LogWarn(SDL_LOG_CATEGORY_SYSTEM, "Ungültiger Größe");

	this->style = size;
	if (this->font != NULL)
		TTF_CloseFont(font);

	font = FontFactory::loadFont(this->fontName);
	this->setStyle(this->style);
	this->setColor(this->color);
}

int Font::getStyle()
{
	return this->style;
}

void Font::setStyle(int style)
{
	if (style < 0)
		SDL_LogWarn(SDL_LOG_CATEGORY_SYSTEM, "Ungültiger Style");

	this->style = style;
	TTF_SetFontStyle(font, style);
}

const char * Font::getFontName()
{
	return this->fontName;
}
