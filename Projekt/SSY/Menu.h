#pragma once
#include <SDL.h>
#include <list>
#include <algorithm>
#include "GUIElement.h"

class Menu
{
private:
	std::list<GUIElement*> objects;
	bool visible;
	bool valid;
	SDL_Rect area;

public:
	Menu();
	Menu(SDL_Rect area);
	Menu(int width, int height);
	Menu(int posX, int posY, int width, int height);
	~Menu();
	/**
	Funktion macht das Element ungültig und führt somit zum neuen Rendern.
	*/
	void invalidate();
	void addObject(GUIElement* object);
	void removeObject(GUIElement* object);
	void onPaint(Renderer* renderer);

	// Getter und Setter

	void setX(int posX);
	void setY(int posY);
	void setWidth(int width);
	void setHeight(int height);
	void setVisible(bool visible);

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	bool isVisible();
	bool isValid();
	std::list<GUIElement*> getObjects();
};

