/*
GenericError.h
Alle Fehlerklassen in einer Header-Datei.
Basisklasse aller Fehlerklassen ist die Klasse GenericError
*/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

//BASISKLASSE
class GenericError
{
public:
	GenericError(std::string msg = "undefinierter Error!") : message(msg) { }
	virtual ~GenericError(void) { }
	virtual std::string what(void) const
	{
		std::string msg = "ERROR: " + message + "\n";
		msg += SDL_GetError();	// Immer den Grund warum was fehlgeschlagen ist bekommen
		return msg + "\n";	// part man sich immer das endl am ende :)
	};

protected:
	std::string message;
};

//SDL_INIT
class SDLInitError : public GenericError
{
public:
	SDLInitError(std::string msg = "SDL_Init Error") : GenericError(msg) { }
};

//SDL_INIT
class SDLImageError : public GenericError
{
public:
	SDLImageError(std::string msg = "SDL_Image Error") : GenericError(msg) { }

	std::string what(void) const override
	{
		std::string msg = "ERROR: " + message + "\n";
		msg += IMG_GetError();	// Immer den Grund warum was fehlgeschlagen ist bekommen
		return msg + "\n";	// part man sich immer das endl am ende :)
	}
};

//Core
class CoreError : public GenericError
{
public:
	CoreError(std::string msg = "Core Error") : GenericError(msg) { }
};

//Window
class WindowError : public GenericError
{
public:
	WindowError(std::string msg = "Window Error") : GenericError(msg) { }
};

//GraphicHelper
class GraphicHelperError : public GenericError
{
public:
	GraphicHelperError(std::string msg = "GraphicHelper Error") : GenericError(msg) { }
};

