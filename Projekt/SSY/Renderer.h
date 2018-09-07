#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Window.h"

class Renderer
{
public:
	// Konstruktoren
	Renderer(Window* window);
	~Renderer();

	// Funktionen zum zeichnen von Texten
	virtual void drawText(const std::string text, const SDL_Rect* rect);
	virtual void drawText(const std::string text, const SDL_Rect* rect, SDL_Color color);
	virtual void drawText(const std::string text, const SDL_Rect* rect, const TTF_Font* font);
	virtual void drawText(const std::string text, const SDL_Rect* rect, const TTF_Font* font, SDL_Color color);

	// Funktionen zum zecihnen von Rechtecken
	virtual void drawRectangle(const SDL_Rect* rect);
	virtual void drawRectangle(const SDL_Rect* rect, SDL_Color color);

	// Funktionen zum Füllen von Rechtecken
	virtual void fillRectangle(const SDL_Rect* rect);
	virtual void fillRectangle(const SDL_Rect* rect, SDL_Color color);
	virtual void fillRectangle(const SDL_Rect* rect, int borderSize, SDL_Color color);

	// Funktionen zum Zeichnen von Texturen
	virtual void drawTexture(const SDL_Rect* rect, SDL_Texture* texture);
	virtual void drawTexture(const SDL_Rect* dstRect, const SDL_Rect* srcRect, SDL_Texture* texture);

	// Funktionen zum Zeichnen des Hintergrundes
	virtual void drawBackground(SDL_Color color);
	virtual void drawBackground(SDL_Texture* texture);
	virtual void drawBackground(const SDL_Rect* rect, SDL_Color color);
	virtual void drawBackground(const SDL_Rect* rect, SDL_Texture* texture);
	virtual void drawBackground(const SDL_Rect* dstRect, const SDL_Rect* srcRect, SDL_Texture* texture);

	// Nötige Renderfunktionen
	void presentRenderer();
private:
	SDL_Renderer * renderer;
};

