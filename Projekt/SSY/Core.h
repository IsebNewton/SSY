#pragma once
#include "Window.h"
#include "GraphicFactory.h"
#include "FontFactory.h"
#include "EventHandler.h"

class Core
{
private:
	Window* window;
	EventHandler eventHandler;

public:
	Core();
	void startGame();
	void onRender();
	~Core();

	static bool quit;
};

