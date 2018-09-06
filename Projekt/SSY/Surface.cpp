#include "Surface.h"

//KONSTRUKTOR
//Surface wird erzeugt und dem übergebenen Fenster eindeutig zugewiesen
Surface::Surface(Window *window_ext)
{
	if (window_ext == nullptr)
		throw SurfaceError();
	window = window_ext;
	surface_window = SDL_GetWindowSurface(window->getWindow());
	aktualisieren();
}


//Lädt eine BMP-Datei über ein Surface zu dem ihm zugewiesenen Fenster
void Surface::laden(const char* name)
{
	SDL_Surface* image = SDL_LoadBMP("Testscreen.bmp");
	SDL_BlitSurface(image, NULL, surface_window, NULL);
	aktualisieren();
}


//Aktualisiert die Oberfläche (das Surface)
void Surface::aktualisieren()
{
	SDL_UpdateWindowSurface(window->getWindow());
}


//DESTRUKTOR
Surface::~Surface()
{
}

