#pragma once
#include "GUILabeled.h"

class Button :
	public GUILabeled
{
public:
	Button() : GUILabeled() 
	{
		initialize();
	};
	Button(std::string text) : GUILabeled(text)
	{
		initialize();
	};
	~Button();

	// Getter und Setter
	void setBorder(int borderSize);
	void setBorderColor(SDL_Color borderColor);
	void setHoveredColor(SDL_Color hoveredColor);
	void setClickedColor(SDL_Color clickedColor);

	int getBorder();
	SDL_Color getBorderColor();
	SDL_Color getHoveredColor();
	SDL_Color getClickedColor();

	// überschriebene Methoden

	virtual void onPaint(Renderer* renderer);

protected:
	void initialize();

private:

	SDL_Color borderColor;
	SDL_Color hoveredColor;
	SDL_Color clickedColor;
	int borderSize;
};

