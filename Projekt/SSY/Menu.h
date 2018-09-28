#pragma once
#include <SDL.h>
#include <list>
#include <algorithm>
#include <cstdarg>
#include "GUIElement.h"
#include "Label.h"

class Menu
{
private:
	std::list<GUIElement*> elements;
	bool visible;
	bool valid;
	SDL_Rect area;
	SDL_Color backgroundColor;
	std::string background;
	SDL_Texture* backgroundTexture = NULL;

	int borderSize;
	SDL_Color borderColor;

	std::string caption;
	Label* captionLabel = NULL;

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
	void addElement(GUIElement* element);

	/**
	Funktion fügt GUIElemente dem Menü hinzu.
	WICHTIG: Man muss als letztes Argument NULL übergeben da sonst eine Speicherzugriffsverletzung stattfindet.

	@params element Liste von GUIElementen welche hinzugefügt werden sollen unnd am Ende NULL 
	*/
	void addElements(GUIElement* element...);
	void removeElement(GUIElement* element);
	void onPaint(Renderer* renderer);

	// Getter und Setter

	void setX(int posX);
	void setY(int posY);
	void setWidth(int width);
	void setHeight(int height);
	void setVisible(bool visible);
	void setBackgroundColor(SDL_Color backgroundColor);
	void setBackground(std::string background);
	void setBorderSize(int size);
	void setBorderColor(SDL_Color color);
	void setCaption(std::string caption);

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	bool isVisible();
	bool isValid();
	SDL_Color getBackgroundColor();
	std::string getBackground();
	std::list<GUIElement*> getElements();
	int getBorderSize();
	SDL_Color getBorderColor();
	std::string getCaption();
	Label* getCaptionLabel();
};

