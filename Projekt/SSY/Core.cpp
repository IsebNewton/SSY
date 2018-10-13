#include "Core.h"
#include <SDL.h>
#include <iostream>
#include "SoundFactory.h"
#include "Color.h"

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
	SoundFactory::initAUDIO();

	if (!window->createWindow())
	{
		throw SDLError();
	}

	// TODO: Eigenschaften des Spiels wie FPS sollen mit einer bestimmten Taste oder Tastenkombination
	// im Window Objectkt angezeigt werden

	int fps = 40;	// TODO: FPS aus der Konfig lesen
	int delay = 1000 / fps;
	Label* frameLabel = new Label();
	frameLabel->setForeColor(Color::WHITE);
	window->addObject(frameLabel);

	SoundFactory::playMusic("Noddinagushpa.mp3", -1);

	eventHandler = EventHandler();
	while (!quit)
	{
		int count = 0;
		long time = SDL_GetTicks();
		while (!quit)
		{
			long frameTime = SDL_GetTicks();

			eventHandler.onHandleEvents(window->getObjects());

			window->onRender();

			if (InputWrapper::isPauseNow())
			{
				SoundFactory::pauseMusic();
				SoundFactory::pauseSound();
			}
			if (InputWrapper::isResumeNow())
			{
				SoundFactory::resumeMusic();
				SoundFactory::resumeSound();
			}

			// Delay setzen damit die FPS runtergesetzt werden.
			if (SDL_GetTicks() - frameTime < delay) {
				SDL_Delay(delay - (SDL_GetTicks() - frameTime));
			}
			if (SDL_GetTicks() - time < 1000)
			{
				count++;
			}
			else
			{
				std::string msg = "FPS: " + std::to_string(count);
				frameLabel->setText(msg);
				break;
			}
		}
		count = 0;
	}
		
	delete window;
	FontFactory::quit();
	GraphicFactory::quit();
	SoundFactory::quit();
	SDL_Quit();
}


void Core::onRender()
{
}

Core::~Core()
{
}
