#include "Menu.h"
#include "Color.h"
#include "GUILabeled.h"


Menu::Menu()
	: Menu(1024, 768)	// TODO: Menü über das ganze Fenster strecken
{ }

Menu::Menu(SDL_Rect area)
	: Menu(area.x, area.y, area.w, area.h)
{ }

Menu::Menu(int width, int height)
	: Menu(0, 0, width, height)
{ }

Menu::Menu(int posX, int posY, int width, int height)
{
	this->area.x = posX;
	this->area.y = posY;
	this->setWidth(width);
	this->setHeight(height);

	this->backgroundColor = Color::TRANSPARENT;
	this->borderSize = 0;
	this->visible = true;
}


Menu::~Menu()
{
	while (!elements.empty())
	{
		removeElement(elements.back());
	}
	if (this->backgroundTexture != NULL)
		SDL_DestroyTexture(this->backgroundTexture);
}

void Menu::invalidate()
{
	this->valid = false;
}

void Menu::addElement(GUIElement * element)
{
	if (element != NULL && !(std::find(elements.begin(), elements.end(), element) != elements.end()))
	{
		element->setX(element->getX() + this->getX());
		element->setY(element->getY() + this->getY());
		this->elements.insert(elements.end(), element);
	}
}

void Menu::addElements(GUIElement* element...)
{
	GUIElement* newElement = element;

	va_list elements;
	va_start(elements, element);

	while (newElement != NULL)
	{
		this->addElement(newElement);
		newElement = va_arg(elements, GUIElement*);
	}
	va_end(elements);
}

void Menu::removeElement(GUIElement * element)
{
	if (element != NULL)
	{
		elements.remove_if([element](GUIElement* value) { return (value == element); });
		delete element;
	}
}

void Menu::onPaint(Renderer* renderer)
{
	if (backgroundTexture != NULL)
	{
		renderer->drawBackground(&area, backgroundTexture);
	}
	else if (std::strlen(background.c_str()) > 0)
	{
		backgroundTexture = renderer->getTexture(background.c_str());
	}
	else
	{
		renderer->drawBackground(&area, backgroundColor);
	}
	renderer->drawRectangle(&area, borderSize, borderColor);
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Getter/Setter										//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//										Setter											//
//////////////////////////////////////////////////////////////////////////////////////////

void Menu::setX(int posX)
{
	this->area.x = posX;
	this->invalidate();
}

void Menu::setY(int posY)
{
	this->area.y = posY;
	this->invalidate();
}

void Menu::setWidth(int width)
{
	if (width < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Breite darf nicht negativ sein.");
		this->area.w = 0;
	}
	else
		this->area.w = width;

	this->invalidate();
}

void Menu::setHeight(int height)
{
	if (height < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Höhe darf nicht negativ sein.");
		this->area.h = 0;
	}
	else
		this->area.h = height;

	this->invalidate();
}

void Menu::setVisible(bool visible)
{
	this->visible = visible;
	for (std::list<GUIElement*>::iterator it = elements.begin(); it != elements.end(); ++it)
	{
		(*it)->setVisible(visible);
	}
	this->invalidate();
}

void Menu::setBackgroundColor(SDL_Color backgroundColor)
{
	this->backgroundColor = backgroundColor;
}

void Menu::setBackground(std::string background)
{
	this->background = background;
	this->backgroundTexture = NULL;	// Damit die Texture wieder aktualisiert wird
}

void Menu::setBorderSize(int size)
{
	this->borderSize = size;
}

void Menu::setBorderColor(SDL_Color color)
{
	this->borderColor = color;
}

void Menu::setCaption(std::string caption)
{
	this->caption = caption;
	if (captionLabel == NULL)
	{
		captionLabel = new Label(caption);
		captionLabel->setWidth(this->getWidth());
		captionLabel->setHeight(20);
		this->addElement(captionLabel);
	}
	captionLabel->setText(caption);
}

//////////////////////////////////////////////////////////////////////////////////////////
//										Getter											//
//////////////////////////////////////////////////////////////////////////////////////////

int Menu::getX()
{
	return this->area.x;
}

int Menu::getY()
{
	return this->area.y;
}

int Menu::getWidth()
{
	return this->area.w;
}

int Menu::getHeight()
{
	return this->area.h;
}

bool Menu::isVisible()
{
	return this->visible;
}

bool Menu::isValid()
{
	return this->valid;
}

SDL_Color Menu::getBackgroundColor()
{
	return this->backgroundColor;
}

std::string Menu::getBackground()
{
	return this->background;
}

std::list<GUIElement*> Menu::getElements()
{
	return elements;
}

int Menu::getBorderSize()
{
	return this->borderSize;
}

SDL_Color Menu::getBorderColor()
{
	return this->borderColor;
}

std::string Menu::getCaption()
{
	return this->caption;
}

Label * Menu::getCaptionLabel()
{
	return this->captionLabel;
}
