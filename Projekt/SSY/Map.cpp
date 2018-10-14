#include "Map.h"
#include "GraphicFactory.h"

Map::Map(const char * file)
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
		map = new Terrain*[height];
		for (int i = 0; i < height; i++)
		{
			map[i] = new Terrain[width];
		}
	}
}

Map::~Map()
{
	for (int i = 0; i < height; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

void Map::createMap()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{ 
			int bpp = mapSurface->format->BytesPerPixel;
			Uint8* pixel = (Uint8 *)pixels + y * mapSurface->pitch + x * bpp;

			Terrain mapObject = getTerrainFrom32(getPixel32(pixel), x, y);
			map[y][x] = mapObject;
		}
	}
}

Terrain Map::getTerrainFrom32(Uint32 pixel, int x, int y)
{
	Terrain terrain;

	switch (pixel)
	{
	case 0x00ff00:	// Green = Grass
		terrain = Terrain(GRASS, BLOCK_SIZE * x, BLOCK_SIZE * y, BLOCK_SIZE);
		break;
	case 0x0000ff:	// Blue = Water
		terrain = Terrain(WATER, BLOCK_SIZE * x, BLOCK_SIZE * y, BLOCK_SIZE);
		break;
	case 0x004000:	// Darkgreen = Wood
		//terrain = Terrain(GRASS, BLOCK_SIZE * x, BLOCK_SIZE * y, BLOCK_SIZE);
		//terrain.setInanimate(new Tree());
		break;
	case 0xFF8000:	// Orange = Sand
		terrain = Terrain(SAND, BLOCK_SIZE * x, BLOCK_SIZE * y, BLOCK_SIZE);
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

SDL_Texture * Map::getTextureFromTerrainType(TerrainType type, Renderer* renderer)
{
	switch (type)
	{
	case GRASS:
		return renderer->getTexture("Grass.jpg");
		break;
	case WATER:
		return renderer->getTexture("Water.jpg");
		break;
	case SAND:
		return renderer->getTexture("Sand.jpg");
		break;
	}
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
	return &map[x][y];
}

void Map::drawMap(Renderer* renderer)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			TerrainType type = map[y][x].getType();
			renderer->drawTexture(&(map[y][x].getArea()), getTextureFromTerrainType(type, renderer));
		}
	}
}
