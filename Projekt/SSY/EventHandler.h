#pragma once
#include <SDL.h>
#include <list>
#include "ObjectControl.h"
#include "InputWrapper.h"

class EventHandler
{
public:
	void onHandleEvents(std::list<ObjectControl*> controls);
	void onHandleMouseEvent(std::list<ObjectControl*> controls);
	void onHandleKeyEvent();

};

