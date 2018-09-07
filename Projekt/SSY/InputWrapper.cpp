#include "InputWrapper.h"

#include <SDL.h>

//Setzt die statischen Attribute der Utility-Klasse
bool InputWrapper::initialized = false;
ButtonState InputWrapper::keyStates[285];
ButtonState InputWrapper::mouseStates[3];
int InputWrapper::mouseX;
int InputWrapper::mouseY;
bool InputWrapper::quit;

void InputWrapper::initialize()
{
	if (!initialized)
	{
		SDL_Init(SDL_INIT_EVENTS);

		quit = false;

		mouseX = 0;
		mouseY = 0;

		mouseStates[0] = ButtonState::UP;
		mouseStates[1] = ButtonState::UP;

		for (int i = 0; i < 285; i++)
		{
			keyStates[i] = ButtonState::UP;
		}

		initialized = true;
	}
}

bool InputWrapper::isInitialized()
{
	return initialized;
}

void InputWrapper::updateEvents()
{
	//Läuft über alle Tasten und setzt es auf den jeweiligen Standard-Zustand falls es sich zuvor in einem der "NOW"-Zustände befand
	for (int i = 0; i < 285; i++)
	{
		if (keyStates[i] == ButtonState::DOWN_NOW)
		{
			keyStates[i] = ButtonState::DOWN;
		}
		if (keyStates[i] == ButtonState::UP_NOW)
		{
			keyStates[i] = ButtonState::UP;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (mouseStates[i] == ButtonState::DOWN_NOW)
		{
			mouseStates[i] = ButtonState::DOWN;
		}
		if (mouseStates[i] == ButtonState::UP_NOW)
		{
			mouseStates[i] = ButtonState::UP;
		}
	}

	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			keyStates[event.key.keysym.scancode] = ButtonState::DOWN_NOW;
			break;
		case SDL_KEYUP:
			keyStates[event.key.keysym.scancode] = ButtonState::UP_NOW;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseStates[event.button.button] = ButtonState::DOWN_NOW;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseStates[event.button.button] = ButtonState::UP_NOW;
			break;
		case SDL_MOUSEMOTION:
			mouseX = event.motion.x;
			mouseY = event.motion.y;
			break;
		default:
			break;
		}
	}
}

int InputWrapper::getMouseX()
{
	return mouseX;
}

int InputWrapper::getMouseY()
{
	return mouseY;
}

bool InputWrapper::isMouseButtonUp(int key)
{
	return (mouseStates[key] == ButtonState::UP);
}

bool InputWrapper::isMouseButtonUpNow(int key)
{
	return (mouseStates[key] == ButtonState::UP_NOW);
}

bool InputWrapper::isMouseButtonDown(int key)
{
	return (mouseStates[key] == ButtonState::DOWN);
}

bool InputWrapper::isMouseButtonDownNow(int key)
{
	return (mouseStates[key] == ButtonState::DOWN_NOW);
}

ButtonState InputWrapper::getMouseButtonState(int key)
{
	return (mouseStates[key]);
}

bool InputWrapper::isKeyUp(int key)
{
	return (keyStates[key] == ButtonState::UP);
}

bool InputWrapper::isKeyUpNow(int key)
{
	return (keyStates[key] == ButtonState::UP_NOW);
}

bool InputWrapper::isKeyDown(int key)
{
	return (keyStates[key] == ButtonState::DOWN);
}

bool InputWrapper::isKeyDownNow(int key)
{
	return (keyStates[key] == ButtonState::DOWN_NOW);
}

ButtonState InputWrapper::getKeyState(int key)
{
	return (keyStates[key]);
}

bool InputWrapper::getQuit()
{
	return quit;
}
