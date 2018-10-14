#pragma once
#include <list>
#include <map>
#include "ObjectControl.h"
#include "Menu.h"
#include "Map.h"

class Map;

class Screen
{
private:
	std::list<ObjectControl*> objects;
	std::map<std::string, Menu*> menus;

	SDL_Texture* background = nullptr;

	Map * map = nullptr;

public:
	Screen();
	Screen(const char* menu);
	~Screen();

	void addObject(ObjectControl* object);

	/**
	Funktion fügt ObjectControls dem Screen hinzu.
	WICHTIG: Man muss als letztes Argument NULL übergeben da sonst eine Speicherzugriffsverletzung stattfindet.

	@params object Liste von ObjectControls welche hinzugefügt werden sollen unnd am Ende NULL
	*/
	void addObjects(ObjectControl* object...);
	void removeObject(ObjectControl* object);

	void addMenu(std::string name, Menu* menu);

	void setBackground(SDL_Texture* background);
	SDL_Texture* getBackground();

	std::list<ObjectControl*> getObjects();
	Menu* getMenu(std::string name);
	std::list<Menu*> getMenus();
	bool hasMap();
};

