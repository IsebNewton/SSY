#include "Map.h"
#include "GraphicFactory.h"

Map::Map(Screen screen, const char * file)
{
	mapSurface = GraphicFactory::loadPicture(file);
	if (mapSurface == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Map konnte nicht geladen werden.");
	}
	else
	{
		width = mapSurface->w;
		height = mapSurface->h;
		pixels = (Uint32 *)mapSurface->pixels;
		createMap(screen);
	}
}

Map::~Map()
{
	for (int i = 0; i < height; i++)
		delete[] map[i];
	delete[] map;
}

void Map::createMap(Screen screen)
{
	map = new Terrain**[height];
	for (int y = 0; y < height; y++)
	{
		map[y] = new Terrain*[width];
		for (int x = 0; x < width; x++)
		{ 
			int bpp = mapSurface->format->BytesPerPixel;
			Uint8* pixel = (Uint8 *)pixels + y * mapSurface->pitch + x * bpp;

			Terrain* mapObject = getTerrainFrom32(getPixel32(pixel));
			map[y][x] = mapObject;
			screen.addObject(mapObject);
		}
	}
}

Terrain * Map::getTerrainFrom32(Uint32 pixel)
{
	Terrain* terrain = NULL;

	switch (pixel)
	{
	case 0x00ff00:	// Green = Grass
		//terrain = new Grass();
		break;
	case 0x0000ff:	// Blue = Water
		//terrain = new Water();
		break;
	case 0x004000:	// Darkgreen = Wood
		//terrain = new Grass();
		//terrain.setInanimate(new Tree());
		break;
	case 0xFF8000:	// Orange = Sand
		//terrain = new Sand();
		break;
	}

	return terrain;
}

Uint32 Map::getPixel32(Uint8 * pixel)
{
	Uint32 resultPixel;
	int bpp = mapSurface->format->BytesPerPixel;

	switch (bpp)
	{
	case 2:
		resultPixel = *(Uint16 *)pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			resultPixel = pixel[0] << 16 | pixel[1] << 8 | pixel[2];
		else
			resultPixel = pixel[0] | pixel[1] << 8 | pixel[2] << 16;
		break;

	case 4:
		resultPixel = *(Uint32 *)pixel;
		break;

	default:
		pixel = 0;
	}
	return resultPixel;
}

int Map::getWidth()
{
	return width;
}

int Map::getHeight()
{
	return height;
}

Terrain * Map::getObject(int x, int y)
{
	return map[x][y];
}
