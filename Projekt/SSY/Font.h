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
	Font(const char* font);
	Font(const char* font, SDL_Color color, int size = 100);
	Font(const char* font, SDL_Color color, int size, int style);
	~Font();

	// Getter/Setter
	TTF_Font* getFont();
	void setFont(TTF_Font* font);
	SDL_Color getColor();
	void setColor(SDL_Color color);
	int getSize();
	void setSize(int size);
	int getStyle();
	void setStyle(int style);
	const char * getFontName();
};

