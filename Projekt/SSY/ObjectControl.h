#pragma once

#include <SDL.h>

struct State
{
	bool clicked = false;
	bool hovered = false;
	bool active = false;
};

class ObjectControl
{
protected:
	ObjectControl(SDL_Rect area);
	ObjectControl(int width, int height);
	ObjectControl(int posX, int posY, int width, int height);
	~ObjectControl();

	void (*onAction)(void);
	bool visible;
	bool valid;
	State state;
	SDL_Rect area;

public:
	/**
	Funktion macht das Element ungültig und führt somit zum neuen Rendern.
	*/
	void invalidate();

	// Getter und Setter

	void setX(int posX);
	void setY(int posY);
	void setWidth(int width);
	void setHeight(int height);
	void setState(State state);
	void setVisible(bool visible);
	void setOnAction(void(*function)(void));

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	State getState();
	bool isVisible();
	bool isValid();

	// Virtuelle Funktionen

	/**
	Zeichnet das Element.
	*/
	virtual void onPaint() { };
};

