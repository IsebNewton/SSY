#include "Core.h"
#include <SDL.h>
#include <iostream>

bool Core::quit = false;

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
		throw SDLError();
	}

	FontFactory::initTTF();
	GraphicFactory::initIMG();

	if (!window->createWindow())
	{
		throw SDLError();
	}

	eventHandler = EventHandler();
	while (!quit)
	{
		long frameTime = SDL_GetTicks();

		eventHandler.onHandleEvents();

		window->onRender();

		// Delay setzen damit die FPS runtergesetzt werden.
		if (SDL_GetTicks() - frameTime < 16) {
			SDL_Delay(16 - (SDL_GetTicks() - frameTime));
		}
	}
		
	delete window;
	FontFactory::quit();
	GraphicFactory::quit();
	SDL_Quit();
}


void Core::onRender()
{
}

Core::~Core()
{
}
