/*
GenericError.h
Alle Fehlerklassen in einer Header-Datei.
Basisklasse aller Fehlerklassen ist die Klasse GenericError
*/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

//BASISKLASSE
class GenericError
{
public:
	GenericError(std::string msg = "Undefinierter Error!") : message(msg) { }
	virtual ~GenericError(void) { }
	virtual std::string what(void) const
	{
		return message;
	}

protected:
	std::string message;
};

//SDL_INIT
class SDLError : public GenericError
{
public:
	SDLError(std::string msg = "SDL Error") : GenericError(msg) { }

	std::string what(void) const override
	{
		std::string msg = "ERROR: " + std::string(message) + "\n";
		msg += SDL_GetError();	// Immer den Grund warum was fehlgeschlagen ist bekommen
		return msg + "\n";	// spart man sich immer das endl am ende :)
	}
};

//IMG
class IMGError : public GenericError
{
public:
	IMGError(std::string msg = "IMG Error") : GenericError(msg) { }

	std::string what(void) const override
	{
		std::string msg = "ERROR: " + std::string(message) + "\n";
		msg += IMG_GetError();	// Immer den Grund warum was fehlgeschlagen ist bekommen
		return msg + "\n";	// spart man sich immer das endl am ende :)
	}
};

//TTF
class TTFError : public GenericError
{
public:
	TTFError(std::string msg = "TTF Error") : GenericError(msg) { }

	std::string what(void) const override
	{
		std::string msg = "ERROR: " + std::string(message) + "\n";
		msg += TTF_GetError();	// Immer den Grund warum was fehlgeschlagen ist bekommen
		return msg + "\n";	// spart man sich immer das endl am ende :)
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

//GraphicFactory
class GraphicFactoryError : public GenericError
{
public:
	GraphicFactoryError(std::string msg = "GraphicHelper Error") : GenericError(msg) { }
};

