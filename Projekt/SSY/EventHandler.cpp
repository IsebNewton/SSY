#include "EventHandler.h"
#include "Core.h"

/**
Behandelt alle Events
*/
void EventHandler::onHandleEvents(std::list<ObjectControl*> controls)
{
	InputWrapper::updateEvents();

	if (InputWrapper::getQuit())
	{
		Core::quit = true;
	}

	onHandleMouseEvent(controls);
	onHandleKeyEvent();
}

void EventHandler::onHandleMouseEvent(std::list<ObjectControl*> controls)
{
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
}

void EventHandler::onHandleKeyEvent()
{
	if (InputWrapper::isKeyDownNow(SDL_SCANCODE_ESCAPE))
	{
		Core::quit = true;
	}
}
