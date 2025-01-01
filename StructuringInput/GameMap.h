#ifndef GameMap_h
#define GameMap_h
#include "Texture.h"
#include "Grid.h"
#include "InputManager.h"

using namespace SDLCore;

class GameMap {
public:

	GameMap();
	~GameMap();
	void Render();
	void Update();

	Grid* mGrid;
	SDL_Rect square;

private:

	Texture* mMapTexture;
	Graphics* mGraphics;
	InputManager* mInput;

	bool isMouseInGrid();
	void CalculateTileIndexFromMouse();
	int mHoveredTile;

	int mGridMinX;
	int mGridMaxX;
	int mGridMinY;
	int mGridMaxY;
	int mOffsetX;
	int mOffsetY;
	int mScaleMapOffset;
};

#endif