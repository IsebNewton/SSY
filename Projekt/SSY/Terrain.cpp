#include "Terrain.h"


Terrain::Terrain(TerrainType type, int x, int y, int size)
{
	this->type = type;
	this->area.x = x;
	this->area.y = y;
	this->area.w = size;
	this->area.h = size;
}

TerrainType Terrain::getType()
{
	return type;
}

SDL_Rect Terrain::getArea()
{
	return area;
}
