#include "EventHandler.h"
#include <SDL.h>
#include "Core.h"

/**
Behandelt alle Events
*/
void EventHandler::onHandleEvents()
{
	InputWrapper::updateEvents();

	if (InputWrapper::getQuit())
	{
		Core::quit = true;
	}

	onHandleMouseEvent();
	onHandleKeyEvent();
}

void EventHandler::onHandleMouseEvent()
{
	// TODO:
}

void EventHandler::onHandleKeyEvent()
{
	if (InputWrapper::isKeyDownNow(SDL_SCANCODE_ESCAPE))
	{
		Core::quit = true;
	}
}
