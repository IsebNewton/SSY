#pragma once
#include <map>
#include "Terrain.h"
#include "Color.h"
#include "Screen.h"

class Screen;

class Map
{
private:
	SDL_Rect viewArea;
	bool viewPortChange;
	int maxViewPortX;
	int maxViewPortY;
	static Renderer* tempRenderer;

	// Mapgröße
	int width;
	int height;

	// MiniMap
	SDL_Texture* miniMap = NULL;
	static SDL_Surface* tempMap;
	SDL_Rect miniMapRect;
	static int updateInterval;

	bool initialized = false;

	SDL_Surface * mapSurface;
	Uint32 * pixels;

	Terrain ** map;

	// Funktionen

	void setMiniMap(SDL_Texture* map);

	// Funktion die als Thread die Minimap updatet
	static int updateMiniMap(void* ptr);

	/**
	Gibt das zugehörige Terrain zum übergebenen Pixel.
	Damit kanneine einfache Map ausgelesen werden
	*/
	Terrain getTerrainFrom32(Uint32 pixel, int x, int y);

	// Textur Map damit nicht immer in der Graphicfactory gesucht werden muss
	std::map<TerrainType, SDL_Texture*> mapTextures;
	Uint32 getPixel32(Uint8* pixel);

public:
	static const int BLOCK_SIZE = 30;
	Map(const char * file);
	~Map();

	// Hilfreiche Funktionen

	void createMap();
	void drawMap(Renderer* renderer);
	void initTextures(Renderer* renderer);
	void startMiniMapUpdater(Renderer* renderer);
	void move();
	void miniMapClick();

	static void setPixel(SDL_Surface* surface, int x, int y, Uint32 pixel);

	// Setter und Getter

	void setViewPort(int x, int y);
	void setMiniMapRect(SDL_Rect rect);

	SDL_Rect getView();
	SDL_Texture* getMiniMap();
	SDL_Rect getMiniMapRect();
	int getWidth();
	int getHeight();
	Terrain* getObject(int x, int y);
	bool isInitialized();
};

