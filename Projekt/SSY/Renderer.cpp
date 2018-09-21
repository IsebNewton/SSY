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
		throw SDLError("Renderer konnte nicht erstellt werden");
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

void Renderer::drawText(const char* text, const SDL_Rect * rect, Font * font)
{
	this->drawText(text, rect, font, SDL_Color{ 0, 0, 0 });
}

void Renderer::drawText(const char* text, const SDL_Rect * rect, Font * font, SDL_Color color)
{
	if (font == NULL || font->getFont() == NULL)
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Schrift zum Rendern darf nicht NULL sein.");

	SDL_Surface * surface = TTF_RenderText_Solid(font->getFont(), text, color);
	SDL_Texture * texture = GraphicFactory::loadTextureFromSurface(renderer, surface);

	// Damit der Text nicht gezogen wird und nicht verpixelt aussieht
	SDL_Rect textRect = SDL_Rect{ rect->x, rect->y, rect->w, rect->h };
	int textWidth = 0;
	int textHeight = 0;
	SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);
	if (rect->w > textWidth)
	{
		// Wenn der eigenltiche Text kleiner ist soll dieser mittig platziert werden
		textRect.x = (int)(rect->x + (rect->w - textWidth) / 2);	
		textRect.w = textWidth;
	}
	if (rect->h > textHeight)
	{
		// Wenn der eigenltiche Text kleiner ist soll dieser mittig platziert werden
		textRect.y = (int)(rect->y + (rect->h - textHeight) / 2);
		textRect.h = textHeight;
	}

	SDL_RenderCopy(renderer, texture, NULL, &textRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Lines												//
//////////////////////////////////////////////////////////////////////////////////////////

void Renderer::drawLine(int x1, int y1, int x2, int y2)
{
	drawLine(x1, y1, x2, y2, SDL_Color{ 0, 0, 0 });
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Renderer::drawLines(const SDL_Point * points, int count)
{
	drawLines(points, count, SDL_Color{ 0, 0, 0 });
}

void Renderer::drawLines(const SDL_Point * points, int count, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawLines(renderer, points, count);
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Points												//
//////////////////////////////////////////////////////////////////////////////////////////

void Renderer::drawPoint(int x, int y)
{
	drawPoint(x, y, SDL_Color{ 0, 0, 0 });
}

void Renderer::drawPoint(int x, int y, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(renderer, x, y);
}

void Renderer::drawPoints(const SDL_Point * points, int count)
{
	drawPoints(points, count, SDL_Color{ 0, 0, 0 });
}

void Renderer::drawPoints(const SDL_Point * points, int count, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoints(renderer, points, count);
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Rectangle											//
//////////////////////////////////////////////////////////////////////////////////////////

void Renderer::drawRectangle(const SDL_Rect * rect)
{
	this->drawRectangle(rect, SDL_Color{ 0, 0, 0 });
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
	this->fillRectangle(rect, SDL_Color{0, 0, 0});
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
