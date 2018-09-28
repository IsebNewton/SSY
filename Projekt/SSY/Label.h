#pragma once
#include "GUILabeled.h"

class Label : public GUILabeled
{
public:
	Label() : GUILabeled() {};
	Label(std::string text) : GUILabeled(text) {};
};

