#pragma once
#include "ObjectControl.h"

class GUIElement :
	public ObjectControl
{
protected:
	GUIElement() : ObjectControl(0, 0, 0, 0) { };
	GUIElement(SDL_Rect area)
		: ObjectControl(area) { };

	SDL_Color backColor;
	SDL_Color foreColor;
	
public:
	// Getter und Setter

	void setForeColor(SDL_Color color);

	SDL_Color getForeColor();
};

