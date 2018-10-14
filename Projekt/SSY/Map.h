#pragma once
#include "Terrain.h"
#include "Color.h"
#include "Screen.h"

class Map
{
private:
	int width;
	int height;

	SDL_Surface * mapSurface;
	Uint32 * pixels;

	Terrain *** map;
	void createMap(Screen screen);
	Terrain* getTerrainFrom32(Uint32 pixel);
	Uint32 getPixel32(Uint8* pixel);

public:
	Map(Screen screen, const char * file);
	~Map();

	int getWidth();
	int getHeight();
	Terrain* getObject(int x, int y);
};

