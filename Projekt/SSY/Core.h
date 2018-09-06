#pragma once
#include "Window.h"
#include "Surface.h"

class Core
{
private:
	Window* window;

public:
	Core();
	void startGame();
	void onRender();
	~Core();
};

