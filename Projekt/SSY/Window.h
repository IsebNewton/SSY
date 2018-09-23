#pragma once
#include <SDL.h>
#include <list>
#include <algorithm>
#include "Menu.h"
#include "Button.h"
#include "ObjectControl.h"
#include "GenericError.h"
#include "Renderer.h"

class Window
{
private:
	std::list<ObjectControl*> objects;
	Menu* activeMenu;

	SDL_Window * window = nullptr;
	Renderer * renderer = nullptr;
	SDL_Texture* background = nullptr;

	void initWindow();

public:
	Window();
	bool createWindow();
	void onRender();

	void addObject(ObjectControl* object);

	/**
	Funktion fügt ObjectControls dem Fenster hinzu.
	WICHTIG: Man muss als letztes Argument NULL übergeben da sonst eine Speicherzugriffsverletzung stattfindet.

	@params object Liste von ObjectControls welche hinzugefügt werden sollen unnd am Ende NULL
	*/
	void addObjects(ObjectControl* object...);
	void removeObject(ObjectControl* object);

	void setMenu(Menu* menu);

	std::list<ObjectControl*> getObjects();
	Menu* getMenu();
	SDL_Window* getWindow();

	~Window();
};

