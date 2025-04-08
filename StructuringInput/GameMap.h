#ifndef GameMap_h
#define GameMap_h
#include "Texture.h"
#include "Grid.h"
#include "InputManager.h"
#include "Animator.h"
#include <queue>

using namespace SDLCore;

class GameMap {
public:

	GameMap();
	~GameMap();
	void Render();
	void Update();

	Grid* mGrid;
	Animator* mAnimator;
	Texture* mMapTexture;
	SDL_Rect square;

	//BFS for path finding
	std::vector<int> BFS(int start, int finish);
	std::vector<int> PathFromBFS(std::vector<int> parentTiles, int finish);

private:

	Graphics* mGraphics;
	InputManager* mInput;

	////for debugging purposes
	//bool isMouseInGrid();
	//void CalculateTileIndexFromMouse();
	//int mHoveredTile;


	void CalculateNeighbors(int* currentTile, int* up, int* right, int* down, int* left);
	int mStartTile;
	int mEndTile;
	bool mHasSearched;

	int mGridMinX;
	int mGridMaxX;
	int mGridMinY;
	int mGridMaxY;
	int mOffsetX;
	int mOffsetY;
	int mScaleMapOffset;
};

#endif