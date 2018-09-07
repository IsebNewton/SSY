#include "Core.h"
#include <SDL.h>
#include <iostream>

Core::Core()
{
	window = new Window();
	
}

/*
Startet den Gameloop und kümmert sich so um das Spiel
*/
void Core::startGame()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw SDLInitError();
	}
	if (!window->createWindow())
	{
		throw  WindowError();
	}

	/*Test der Klasse GraphicHelper*/
	try
	{
		SDL_Surface* picture = GraphicFactory::loadPicture("Testscreen.bmp");
		SDL_BlitSurface(picture, NULL, SDL_GetWindowSurface(window->getWindow()), NULL);
		SDL_UpdateWindowSurface(window->getWindow());
	}
	catch (const GenericError error)
	{
		throw error;
	}
	/*Ende des Tests*/

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		long frameTime = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		// Delay setzen damit die FPS runtergesetzt werden.
		if (SDL_GetTicks() - frameTime < 30) {
			SDL_Delay(30 - (SDL_GetTicks() - frameTime));
		}
	}
		
	delete window;
	GraphicFactory::quit();
	SDL_Quit();
}


void Core::onRender()
{
}

Core::~Core()
{
}
