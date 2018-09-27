#pragma once

#include <SDL.h>
#include "Events.h"
#include "InputWrapper.h"
#include "Renderer.h"

struct State
{
	bool clicked = false;
	bool pressed = false;
	bool hovered = false;
	bool active = false;
};

class ObjectControl : Events
{
protected:
	ObjectControl();
	ObjectControl(SDL_Rect area);
	ObjectControl(int width, int height);
	ObjectControl(int posX, int posY, int width, int height);

	void (*onAction)(void) = []() {};
	bool visible;
	bool valid;
	State state;
	SDL_Rect area;

	SDL_Color backColor;
	SDL_Texture* background = NULL;

public:
	~ObjectControl();
	/**
	Funktion macht das Element ungültig und führt somit zum neuen Rendern.
	*/
	void invalidate();

	// Getter und Setter

	void setX(int posX);
	void setY(int posY);
	void setWidth(int width);
	void setHeight(int height);
	void setVisible(bool visible);
	void setOnAction(void(*function)(void));
	void setBackColor(SDL_Color color);
	void setBackground(SDL_Texture* background);

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	State getState();
	bool isVisible();
	bool isValid();
	SDL_Color getBackColor();
	SDL_Texture* getBackground();

	// Virtuelle Funktionen

	/**
	Zeichnet das Element.
	*/
	virtual void onPaint(Renderer* renderer) {};

	/**
	Event wird aufgerufen wenn die Maus über dem Element ist.
	*/
	virtual void onMouseOver() override {};

	/**
	Event wird aufgerufen wenn die Maus aus dem Element ist.
	*/
	virtual void onMouseLeave() override {};

	/**
	Event wird aufgerufen wenn auf das Element geklickt wird.
	*/
	virtual void onClick() override
	{
		onAction();
	};

	/**
	Event wird aufgerufen wenn sich die Größe des Elements geklickt wird.
	*/
	virtual void onResize() override {};
};

