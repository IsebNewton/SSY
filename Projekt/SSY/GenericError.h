/*
GenericError.h
Alle Fehlerklassen in einer Header-Datei.
Basisklasse aller Fehlerklassen ist die Klasse GenericError
*/

#pragma once
#include <string>

//BASISKLASSE
class GenericError
{
public:
	GenericError(std::string msg = "undefinierter Error!") : message(msg) { }
	virtual ~GenericError(void) { }
	virtual std::string what(void) const { return "ERROR: " + message; }
protected:
	std::string message;
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

//Surface
class SurfaceError : public GenericError
{
public:
	SurfaceError(std::string msg = "Surface Error") : GenericError(msg) { }
};

