#pragma once
#include <SDL.h>
#include <list>
#include "ObjectControl.h"
#include "InputWrapper.h"
#include "Window.h"

class EventHandler
{
public:
	void onHandleEvents(Window* window);
	void onHandleMouseEvent(Window* window);
	void onHandleKeyEvent();

};

