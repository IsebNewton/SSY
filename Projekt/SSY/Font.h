#pragma once
#include <string>
#include <SDL_ttf.h>
#include "FontFactory.h"

class Font
{
private:
	SDL_Color color;
	TTF_Font * font;
	int size;
	int style;
	const char * fontName;

public:
	// Konstruktoren
	Font(const char* font = "Arial");
	Font(const char* font, int size = 11);
	Font(const char* font, int size, int style);

	// Getter/Setter
	TTF_Font* getFont();
	void setFont(TTF_Font* font);
	int getSize();
	void setSize(int size);
	int getStyle();
	void setStyle(int style);
	const char * getFontName();
};

