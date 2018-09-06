#pragma once
#include "Window.h"

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

