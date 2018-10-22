#pragma once
#include "ObjectControl.h"
#include "Color.h"
#include "Subject.h"

enum TerrainType
{
	GRASS,
	SAND,
	WATER,
	SWAMP,
	EARTH
};

class Terrain : public Subject
{
private:
	TerrainType type;
	SDL_Rect area;
	//MapObject* object;

public:
	Terrain() {};
	Terrain(TerrainType type, int x, int y, int size);

	TerrainType getType();
	SDL_Rect getArea();
	//bool canObjectBeOn(MapObject& object);
};

