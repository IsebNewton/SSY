#include <math.h>
#include "Map.h"
#include "GraphicFactory.h"
#include "Config.h"

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
	// set View
	int menuHeight = ((float)Config::windowHeight * Config::menuHeight);

	setViewPort(0, 0);
	viewArea.w = Config::windowWidth;
	viewArea.h = Config::windowHeight - menuHeight;

	// Set miniMap
	miniMapRect.x = 0;
	miniMapRect.y = viewArea.h;
	miniMapRect.h = menuHeight;
	miniMapRect.w = menuHeight;

	maxViewPortX = width * BLOCK_SIZE - viewArea.w;
	maxViewPortY = height * BLOCK_SIZE - viewArea.h;
}

Map::~Map()
{
	for (int i = 0; i < height; i++)
	{
		delete[] map[i];
	}
	delete[] map;

	if (tempMap != NULL)
		//SDL_FreeSurface(tempMap); // Führt noch zu Fehlern
	if (miniMap != NULL)
		SDL_DestroyTexture(miniMap);
}

//////////////////////////////////////////////////////////////////////////////////////////
//							Hilfreiche Funktionen										//
//////////////////////////////////////////////////////////////////////////////////////////

void Map::createMap()
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{ 
			int bpp = mapSurface->format->BytesPerPixel;
			Uint8* pixel = (Uint8 *)pixels + y * mapSurface->pitch + x * bpp;

			Terrain mapObject = getTerrainFrom32(getPixel32(pixel), x, y);
			//mapObject.addObserver(this); // TODO: Konvertierung von Map in Observer<Subject> nicht möglich
			map[y][x] = mapObject;
		}
	}

	// Minimap das erste mal setzen
	miniMap = Renderer::getInstance()->getTexture(mapSurface);
}

void Map::drawMap(Renderer* renderer)
{
	int startY = floor(viewArea.y / BLOCK_SIZE);
	int startX = floor(viewArea.x / BLOCK_SIZE);
	int countX = startX + ceil((float)(viewArea.w) / BLOCK_SIZE);
	int countY = startY + ceil((float)(viewArea.h) / BLOCK_SIZE);

	for (int y = startY; y < countY; y++)
	{
		for (int x = startX; x < countX; x++)
		{
			Terrain terrain = map[y][x];
			TerrainType type = terrain.getType();
			SDL_Rect rect = terrain.getArea();
			// Maßen an die View anpassen
			rect.x -= viewArea.x;
			rect.y -= viewArea.y;
			renderer->drawTexture(&rect, mapTextures.find(type)->second);
		}
	}

	// MiniMap zeichnen
	renderer->drawTexture(&miniMapRect, miniMap);

	miniMapViewRect.x = miniMapRect.x;
	miniMapViewRect.y = miniMapRect.y;
	miniMapViewRect.x += ceil(((float)miniMapRect.w / width) * (viewArea.x / BLOCK_SIZE));
	miniMapViewRect.y += ceil(((float)miniMapRect.h / height) * (viewArea.y / BLOCK_SIZE));
	miniMapViewRect.w = floor(((float)miniMapRect.w / width) * (countX - startX));
	miniMapViewRect.h = floor(((float)miniMapRect.h / height) * (countY - startY));
	renderer->drawRectangle(&miniMapViewRect, Color::WHITE);
}

void Map::initTextures(Renderer* renderer)
{
	mapTextures.insert(std::pair<TerrainType, SDL_Texture*>(GRASS, renderer->getTexture("Grass.jpg")));
	mapTextures.insert(std::pair<TerrainType, SDL_Texture*>(WATER, renderer->getTexture("Water.jpg")));
	mapTextures.insert(std::pair<TerrainType, SDL_Texture*>(SAND, renderer->getTexture("Sand.jpg")));

	initialized = true;
}

int Map::updateMiniMap(const Terrain& terrain, int x, int y)
{
	// Kopie erstellen
	SDL_Surface temp = *mapSurface;
	tempMap = &temp;

	// Benutzen von Terrain
	Terrain tempTerrain = terrain;
	int bpp = tempMap->format->BytesPerPixel;

	// Pixel Updaten
	Uint32 pixel = 0xFFFFFF;
	switch (tempTerrain.getType())
	{
	case GRASS:
		pixel = 0x00FF00;
		break;
	case SAND:
		pixel = 0xFF8000;
		break;
	case WATER:
		pixel = 0x0000FF;
		break;
	}
	Map::setPixel(tempMap, x, y, pixel);

	// Neue Textur erstellen
	SDL_Texture* map = NULL;
	map = Renderer::getInstance()->getTexture(tempMap);
	if (map == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Fehler beim erstellen der MiniMap.");
	}

	// Alte Textur freigeben
	if (miniMap != NULL)
	{
		SDL_DestroyTexture(miniMap);
	}
	miniMap = map;

	return 0;
}

void Map::move()
{
	int move = BLOCK_SIZE;
	if (InputWrapper::getMouseY() >= Config::windowHeight - 1)
	{
		setViewPort(viewArea.x, viewArea.y + move);
	}
	if (InputWrapper::getMouseX() >= Config::windowWidth - 1)
	{
		setViewPort(viewArea.x + move, viewArea.y);
	}
	if (InputWrapper::getMouseY() <= 0)
	{
		setViewPort(viewArea.x, viewArea.y - move);
	}
	if (InputWrapper::getMouseX() <= 0)
	{
		setViewPort(viewArea.x - move, viewArea.y);
	}
}

void Map::miniMapClick()
{
	float blockSizeMapX = (float)miniMapRect.w / width;
	float blockSizeMapY = (float)miniMapRect.h / height;
	// Mauspostion soll mittig im Rechteck liegen -> hälfte des rechtecks subtrahieren
	float mousePositionX = InputWrapper::getMouseX() - miniMapRect.x - (float)miniMapViewRect.w / 2;
	float mousePositionY = InputWrapper::getMouseY() - miniMapRect.y - (float)miniMapViewRect.h / 2;
	int x = ceil(mousePositionX / blockSizeMapX) * BLOCK_SIZE;
	int y = ceil(mousePositionY / blockSizeMapY) * BLOCK_SIZE;
	setViewPort(x, y);
}

void Map::setPixel(SDL_Surface * surface, int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *)p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
//								Getter und Setter										//
//////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//									 Setter												//
//////////////////////////////////////////////////////////////////////////////////////////

void Map::setMiniMap(SDL_Texture * map)
{
	miniMap = map;
}

void Map::setViewPort(int x, int y)
{
	if (x >= 0 && x <= maxViewPortX)
	{
		viewArea.x = x;
	}
	else if (x < 0)
	{
		viewArea.x = 0;
	}
	else if (x > maxViewPortX)
	{
		viewArea.x = maxViewPortX;
	}
	if (y >= 0 && y <= maxViewPortY)
	{
		viewArea.y = y;
	}
	else if (y < 0)
	{
		viewArea.y = 0;
	}
	else if (y > maxViewPortY)
	{
		viewArea.y = maxViewPortY;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
//									 Getter												//
//////////////////////////////////////////////////////////////////////////////////////////

SDL_Rect Map::getView()
{
	return viewArea;
}

SDL_Texture * Map::getMiniMap()
{
	return miniMap;
}

SDL_Rect Map::getMiniMapRect()
{
	return miniMapRect;
}

Terrain Map::getTerrainFrom32(Uint32 pixel, int x, int y)
{
	Terrain terrain;

	switch (pixel)
	{
	case 0x00FF00:	// Green = Grass
		terrain = Terrain(GRASS, BLOCK_SIZE * x, BLOCK_SIZE * y, BLOCK_SIZE);
		break;
	case 0x0000FF:	// Blue = Water
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
	return &map[y][x];
}

bool Map::isInitialized()
{
	return initialized;
}

//////////////////////////////////////////////////////////////////////////////////////////
//									Override											//
//////////////////////////////////////////////////////////////////////////////////////////

void Map::onNotify(const Terrain & entity)
{
	Terrain terrain = entity;
	updateMiniMap(entity, terrain.getArea().x, terrain.getArea().y);
}

