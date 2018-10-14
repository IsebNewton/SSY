#pragma once
#include "Terrain.h"
#include "Color.h"
#include "Screen.h"

class Screen;

class Map
{
private:
	int width;
	int height;

	SDL_Surface * mapSurface;
	Uint32 * pixels;

	Terrain ** map;
	Terrain getTerrainFrom32(Uint32 pixel, int x, int y);
	Uint32 getPixel32(Uint8* pixel);

	SDL_Texture* getTextureFromTerrainType(TerrainType type, Renderer* renderer);

public:
	static const int BLOCK_SIZE = 20;
	Map(const char * file);
	~Map();

	void createMap();

	int getWidth();
	int getHeight();
	Terrain* getObject(int x, int y);
	void drawMap(Renderer* renderer);
};

