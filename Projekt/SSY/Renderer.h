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
	void drawText(const char* text, const SDL_Rect* rect, Font* font);
	void drawText(const char* text, const SDL_Rect* rect, Font* font, SDL_Color color);

	// Funktionen zum Zeichnen von Linien
	void drawLine(int x1, int y1, int x2, int y2);
	void drawLine(int x1, int y1, int x2, int y2, SDL_Color color);
	void drawLines(const SDL_Point* points, int count);
	void drawLines(const SDL_Point* points, int count, SDL_Color color);

	// Funktionen zum Zeichnen von Punkten
	void drawPoint(int x, int y);
	void drawPoint(int x, int y, SDL_Color color);
	void drawPoints(const SDL_Point* points, int count);
	void drawPoints(const SDL_Point* points, int count, SDL_Color color);

	// Funktionen zum Zeichnen von Rechtecken
	void drawRectangle(const SDL_Rect* rect);
	void drawRectangle(const SDL_Rect* rect, SDL_Color color);
	void drawRectangle(const SDL_Rect* rect, int borderSize, SDL_Color color);

	// Funktionen zum Füllen von Rechtecken
	void fillRectangle(const SDL_Rect* rect);
	void fillRectangle(const SDL_Rect* rect, SDL_Color color);

	// Funktionen zum Zeichnen von Bildern
	void drawPicture(const SDL_Rect* rect, SDL_Surface* surface);
	void drawPicture(const SDL_Rect* dstRect, const SDL_Rect* srcRect, SDL_Surface* surface);

	// Funktionen zum Zeichnen von Texturen
	void drawTexture(const SDL_Rect* rect, SDL_Texture* texture);
	void drawTexture(const SDL_Rect* dstRect, const SDL_Rect* srcRect, SDL_Texture* texture);

	// Funktionen zum Zeichnen des Hintergrundes
	void drawBackground(SDL_Color color);
	void drawBackground(SDL_Texture* texture);
	void drawBackground(SDL_Surface* surface);
	void drawBackground(const SDL_Rect* rect, SDL_Color color);
	void drawBackground(const SDL_Rect* rect, SDL_Surface* surface);
	void drawBackground(const SDL_Rect* rect, SDL_Texture* texture);
	void drawBackground(const SDL_Rect* dstRect, const SDL_Rect* srcRect, SDL_Surface* surface);

	// Nötige Renderfunktionen
	SDL_Texture* getTexture(SDL_Surface* surface);
	SDL_Texture* getTexture(const char * path);
	void presentRenderer();
private:
	SDL_Renderer * renderer;
};

