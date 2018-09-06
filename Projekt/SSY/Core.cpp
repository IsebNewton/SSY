#include "Core.h"
#include <SDL.h>
#include <iostream>

Core::Core()
{
	window = new Window();
	
}

void Core::startGame()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "ERROR: " << SDL_GetError() << std::endl;
	}
	if (!window->createWindow())
	{
		std::cerr << "ERROR: " << SDL_GetError() << std::endl;
	}

	/*Test der Klasse Surface*/
	try
	{
		Surface *testbild = new Surface(window);
		testbild->laden("Testscreen.bmp");
	}
	catch (SurfaceError &obj)
	{
		std::cerr << obj.what() << std::endl;
	}
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
