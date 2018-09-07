#include "Renderer.h"

/**
Konstruktor erzeugt ein neuen Renderer für das übergebene Fenster.

@param window Fenster für welches ein Renderer erstellt werden soll.
*/
Renderer::Renderer(SDL_Window* window)
{
	if (window == NULL)
		throw GenericError("Window des Renderers darf nicht null sein");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);
	if (renderer == NULL)
		throw GenericError("Renderer konnte nicht erstellt werden");
}

/**
Löscht den erzeugten Renderer
*/
Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Text												//
//////////////////////////////////////////////////////////////////////////////////////////

void Renderer::drawText(const std::string text, const SDL_Rect * rect)
{
	// TODO:
}

void Renderer::drawText(const std::string text, const SDL_Rect * rect, SDL_Color color)
{
	// TODO:
}

void Renderer::drawText(const std::string text, const SDL_Rect * rect, const TTF_Font * font)
{
	// TODO:
}

void Renderer::drawText(const std::string text, const SDL_Rect * rect, const TTF_Font * font, SDL_Color color)
{
	// TODO:
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Rectangle											//
//////////////////////////////////////////////////////////////////////////////////////////

void Renderer::drawRectangle(const SDL_Rect * rect)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderDrawRect(renderer, rect);
}

void Renderer::drawRectangle(const SDL_Rect * rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, rect);
}

void Renderer::drawRectangle(const SDL_Rect * rect, int borderSize, SDL_Color color)
{
	if (borderSize > 0)
	{
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_Rect borderRect;

		// Linken Rand zeichnen
		borderRect.x = rect->x;
		borderRect.y = rect->y;
		borderRect.w = borderSize;
		borderRect.h = rect->h;
		this->fillRectangle(&borderRect, color);

		// Oberen Rand zeichnen
		borderRect.w = rect->w;
		borderRect.h = borderSize;
		this->fillRectangle(&borderRect, color);

		// Rechten Rand zeichnen
		borderRect.x = rect->x + rect->w - borderSize;
		borderRect.h = rect->h;
		borderRect.w = borderSize;
		this->fillRectangle(&borderRect, color);

		// Unteren Rand zeichnen
		borderRect.x = rect->x;
		borderRect.y = rect->y + rect->h - borderSize;
		borderRect.w = rect->w;
		borderRect.h = borderSize;
		this->fillRectangle(&borderRect, color);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
//									FillRectangle										//
//////////////////////////////////////////////////////////////////////////////////////////

void Renderer::fillRectangle(const SDL_Rect * rect)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, rect);
}

void Renderer::fillRectangle(const SDL_Rect * rect, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, rect);
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Picture												//
//////////////////////////////////////////////////////////////////////////////////////////

void Renderer::drawPicture(const SDL_Rect * rect, SDL_Surface* surface)
{
	SDL_Texture* texture = GraphicFactory::loadTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, rect);
	SDL_DestroyTexture(texture);
}

void Renderer::drawPicture(const SDL_Rect * dstRect, const SDL_Rect * srcRect, SDL_Surface* surface)
{
	SDL_Texture* texture = GraphicFactory::loadTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, srcRect, dstRect);
	SDL_DestroyTexture(texture);
}

void Renderer::drawTexture(const SDL_Rect * rect, SDL_Texture * texture)
{
	SDL_RenderCopy(renderer, texture, NULL, rect);
}

void Renderer::drawTexture(const SDL_Rect * dstRect, const SDL_Rect * srcRect, SDL_Texture * texture)
{
	SDL_RenderCopy(renderer, texture, srcRect, dstRect);
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Background											//
//////////////////////////////////////////////////////////////////////////////////////////

void Renderer::drawBackground(SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(renderer);
}

void Renderer::drawBackground(SDL_Texture * texture)
{
	this->drawTexture(NULL, texture);
}

void Renderer::drawBackground(SDL_Surface* surface)
{
	this->drawPicture(NULL, surface);
}

void Renderer::drawBackground(const SDL_Rect * rect, SDL_Color color)
{
	this->fillRectangle(rect, color);
}

void Renderer::drawBackground(const SDL_Rect * rect, SDL_Surface* surface)
{
	this->drawPicture(rect, surface);
}

void Renderer::drawBackground(const SDL_Rect * dstRect, const SDL_Rect * srcRect, SDL_Surface* surface)
{
	this->drawPicture(dstRect, srcRect, surface);
}

//////////////////////////////////////////////////////////////////////////////////////////
//							Zusätzliche Renderfunktionen								//
//////////////////////////////////////////////////////////////////////////////////////////

SDL_Texture * Renderer::getTexture(SDL_Surface * surface)
{
	return GraphicFactory::loadTextureFromSurface(renderer, surface);
}

SDL_Texture * Renderer::getTexture(const char * path)
{
	return GraphicFactory::loadTexture(renderer, path);
}

void Renderer::presentRenderer()
{
	SDL_RenderPresent(renderer);
}
