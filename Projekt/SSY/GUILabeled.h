#pragma once
#include "GUIElement.h"
#include "Font.h"

class GUILabeled : public GUIElement
{
protected:
	GUILabeled() : GUIElement()
	{
		initialize();
	};
	GUILabeled(std::string text) : GUIElement()
	{
		initialize();
		this->setText(text);
	};
	GUILabeled(SDL_Rect area)
		: GUIElement(area)
	{
		initialize();
	};
	~GUILabeled();

	SDL_Texture * picture = NULL;
	SDL_Texture * textTexture = NULL;
	std::string text;
	Font * font;
	SDL_Rect textRect;

	void initialize();

public:
	// Getter und Setter

	void setFont(Font * font);
	void setPicture(SDL_Texture* picture);
	void setText(std::string text);

	Font* getFont();
	SDL_Texture* getPicture();
	std::string getText();

	virtual void onPaint(Renderer* renderer);
};

