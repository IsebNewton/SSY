#include "EventHandler.h"
#include "Core.h"

/**
Behandelt alle Events
*/
void EventHandler::onHandleEvents(Window* window)
{
	InputWrapper::updateEvents();

	if (InputWrapper::isQuit())
	{
		Core::quit = true;
	}

	onHandleMouseEvent(window);
	onHandleKeyEvent();
}

void EventHandler::onHandleMouseEvent(Window* window)
{
	std::list<ObjectControl*> controls = window->getScreen()->getObjects();
	for (std::list<ObjectControl*>::iterator it = controls.begin();
		it != controls.end(); ++it)
	{
		if ((*it)->getState().pressed)
		{
			(*it)->onClick();
		}
		if ((*it)->getState().hovered)
		{
			(*it)->onMouseOver();
		}
	}

	if (window->getScreen()->hasMap())
	{
		SDL_Rect miniMap = window->getScreen()->getMap()->getMiniMapRect();
		if (InputWrapper::getMouseX() >= miniMap.x && InputWrapper::getMouseX() <= miniMap.x + miniMap.w
			&& InputWrapper::getMouseY() >= miniMap.y && InputWrapper::getMouseY() <= miniMap.y + miniMap.h
			&& InputWrapper::isMouseButtonDown(SDL_BUTTON_LEFT))
		{
			window->getScreen()->getMap()->miniMapClick();
		}
	}
}

void EventHandler::onHandleKeyEvent()
{
	if (InputWrapper::isKeyDownNow(SDL_SCANCODE_ESCAPE))
	{
		Core::quit = true;
	}
}
