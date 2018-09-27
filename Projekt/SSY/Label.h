#pragma once
#include "GUILabeled.h"

class Label : public GUILabeled
{
public:
	Label(std::string text) : GUILabeled(text) {};
};

