#pragma once
#include <SDL.h>
#include <string>
#include "GraphicFactory.h"
#include "Font.h"

class Renderer
{
public:
	// Konstruktoren
	Renderer(SDL_Window* window);
	~Renderer();

	// Funktionen zum zeichnen von Texten
	virtual void drawText(const char* text, const SDL_Rect* rect, Font* font);
	virtual void drawText(const char* text, const SDL_Rect* rect, Font* font, SDL_Color color);

	// Funktionen zum zecihnen von Rechtecken
	virtual void drawRectangle(const SDL_Rect* rect);
	virtual void drawRectangle(const SDL_Rect* rect, SDL_Color color);
	virtual void drawRectangle(const SDL_Rect* rect, int borderSize, SDL_Color color);

	// Funktionen zum Füllen von Rechtecken
	virtual void fillRectangle(const SDL_Rect* rect);
	virtual void fillRectangle(const SDL_Rect* rect, SDL_Color color);

	// Funktionen zum Zeichnen von Bildern
	virtual void drawPicture(const SDL_Rect* rect, SDL_Surface* surface);
	virtual void drawPicture(const SDL_Rect* dstRect, const SDL_Rect* srcRect, SDL_Surface* surface);

	// Funktionen zum Zeichnen von Texturen
	virtual void drawTexture(const SDL_Rect* rect, SDL_Texture* texture);
	virtual void drawTexture(const SDL_Rect* dstRect, const SDL_Rect* srcRect, SDL_Texture* texture);

	// Funktionen zum Zeichnen des Hintergrundes
	virtual void drawBackground(SDL_Color color);
	virtual void drawBackground(SDL_Texture* texture);
	virtual void drawBackground(SDL_Surface* surface);
	virtual void drawBackground(const SDL_Rect* rect, SDL_Color color);
	virtual void drawBackground(const SDL_Rect* rect, SDL_Surface* surface);
	virtual void drawBackground(const SDL_Rect* dstRect, const SDL_Rect* srcRect, SDL_Surface* surface);

	// Nötige Renderfunktionen
	SDL_Texture* getTexture(SDL_Surface* surface);
	SDL_Texture* getTexture(const char * path);
	void presentRenderer();
private:
	SDL_Renderer * renderer;
};

