#pragma once
#include <SDL.h>

class Color
{
public:
	static SDL_Color fromRGB(Uint8 r, Uint8 g, Uint8 b)
	{
		return SDL_Color{ r, g, b, 255 };
	}
	static SDL_Color fromARGB(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		return SDL_Color{ r, g, b, a };
	}

	// Basic Colors

	static const SDL_Color BLACK;
	static const SDL_Color SILVER;
	static const SDL_Color GRAY;
	static const SDL_Color WHITE;
	static const SDL_Color MAROON;
	static const SDL_Color RED;
	static const SDL_Color PURPLE;
	static const SDL_Color FUCHSIA;
	static const SDL_Color GREEN;
	static const SDL_Color LIME;
	static const SDL_Color OLIVE;
	static const SDL_Color YELLOW;
	static const SDL_Color NAVY;
	static const SDL_Color BLUE;
	static const SDL_Color TEAL;
	static const SDL_Color AQUA;

	// Other Colors

	static const SDL_Color TRANSPARENT;
	static const SDL_Color DARK_RED;
	static const SDL_Color DARK_GREEN;
	static const SDL_Color DARK_BLUE;
	static const SDL_Color DARK_GRAY;
	static const SDL_Color LIGHT_GREEN;
	static const SDL_Color LIGHT_BLUE;
	static const SDL_Color LIGHT_YELLOW;
	static const SDL_Color LIGHT_GRAY;
};
