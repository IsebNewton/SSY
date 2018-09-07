#include "Renderer.h"

/**
Konstruktor erzeugt ein neuen Renderer für das übergebene Fenster.

@param window Fenster für welches ein Renderer erstellt werden soll.
*/
Renderer::Renderer(Window* window)
{
	if (window == NULL || window->getWindow() == NULL)
		throw GenericError("Window des Renderers darf nicht null sein");

	renderer = SDL_CreateRenderer(window->getWindow(), -1, SDL_RENDERER_TARGETTEXTURE);
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

void Renderer::fillRectangle(const SDL_Rect * rect, int borderSize, SDL_Color color)
{
	// TODO:
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Texture												//
//////////////////////////////////////////////////////////////////////////////////////////

void Renderer::drawTexture(const SDL_Rect * rect, SDL_Texture * texture)
{
	if (texture == NULL)
		throw GenericError("Renderer: Textur darf nicht NULL sein");
	SDL_RenderCopy(renderer, texture, NULL, rect);
}

void Renderer::drawTexture(const SDL_Rect * dstRect, const SDL_Rect * srcRect, SDL_Texture * texture)
{
	if (texture == NULL)
		throw GenericError("Renderer: Textur darf nicht NULL sein");
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

void Renderer::drawBackground(const SDL_Rect * rect, SDL_Color color)
{
	this->fillRectangle(rect, color);
}

void Renderer::drawBackground(const SDL_Rect * rect, SDL_Texture * texture)
{
	this->drawTexture(rect, texture);
}

void Renderer::drawBackground(const SDL_Rect * dstRect, const SDL_Rect * srcRect, SDL_Texture * texture)
{
	this->drawTexture(dstRect, srcRect, texture);
}

//////////////////////////////////////////////////////////////////////////////////////////
//							Zusätzliche Renderfunktionen								//
//////////////////////////////////////////////////////////////////////////////////////////

void Renderer::presentRenderer()
{
	SDL_RenderPresent(renderer);
}
