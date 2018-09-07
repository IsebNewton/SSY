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
		throw new SDLInitError();
	}
	if (!window->createWindow())
	{
		throw new WindowError();
	}

	/*Test der Klasse Surface*/
	Surface *testbild = new Surface(window);
	testbild->laden("Testscreen.bmp");
	/*Ende des Tests*/

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
		
	delete window;
	SDL_Quit();
}


void Core::onRender()
{
}

Core::~Core()
{
}
