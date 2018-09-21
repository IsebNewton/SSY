#include "Font.h"



Font::Font(const char * font)
{
	this->fontName = font;
	this->size = 24;
	this->font = FontFactory::getFont(font, this->size);
}

Font::Font(const char * font, int size)
{
	this->fontName = font;
	this->size = 24;
	this->font = FontFactory::getFont(font, size);
}

Font::Font(const char * font, int size, int style)
{
	this->fontName = font;
	this->size = size;
	this->font = FontFactory::getFont(font, size);
	this->setStyle(style);
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

int Font::getSize()
{
	return this->size;
}

void Font::setSize(int size)
{
	if (size < 0)
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Ungültiger Größe");

	if (size != this->size)
	{
		this->size = size;

		font = FontFactory::getFont(this->fontName, size);

		this->setStyle(this->style);
	}
}

int Font::getStyle()
{
	return this->style;
}

void Font::setStyle(int style)
{
	if (style < 0)
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Ungültiger Style");
	else
	{
		this->style = style;
		TTF_SetFontStyle(font, style);
	}
}

const char * Font::getFontName()
{
	return this->fontName;
}
