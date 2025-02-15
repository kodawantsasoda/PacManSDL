#include "GameMap.h"

GameMap::GameMap() {

	//instances being referenced
	mGraphics = Graphics::Instance();
	mInput = InputManager::Instance();

	//clipping the sprite sheet to only incude the map
	mMapTexture = new Texture("PMSpriteSheet.png");
	mMapTexture->ClipLocalTexture(0, 0, 224, 248);
	
	//reference rect for our grid. All squares in the grid will be based on these dimensions
	//offset used to scale map properly so that theres enough room for other entities like text or sprites
	mScaleMapOffset = 5;
	int columns = 28, rows = 31;
	if (mGraphics->SCREEN_WIDTH > mGraphics->SCREEN_HEIGHT) {

		square.w = mGraphics->SCREEN_HEIGHT / rows - mScaleMapOffset;
		square.h = square.w;
	}
	else {
		square.w = mGraphics->SCREEN_WIDTH / columns - mScaleMapOffset;
		square.h = square.w;
	}
	square.x = (abs(mGraphics->SCREEN_WIDTH - square.w * columns) / 2);
	square.y = (abs(mGraphics->SCREEN_HEIGHT - square.h * rows) / 2);

	//lining up the texture with the position of the grid
	mMapTexture->PositionTextureArea(square.x, square.y);

	//creating a grid based on our reference rectangle created from above; and based on the original pacman tiles
	mGrid = new Grid(square, columns, rows);

	//getting the min/max of our x/y valyes to identify the bounds of the map
	mGridMinX = mGrid->mTiles[0].mTile.x;
	mGridMaxX = mGrid->mTiles[mGrid->mTiles.size() - 1].mTile.x;
	mGridMinY = mGrid->mTiles[0].mTile.y;
	mGridMaxY = mGrid->mTiles[mGrid->mTiles.size() - 1].mTile.y;

	//offset to include the squares that are to the right of x/y's max
	mOffsetX = square.w;
	mOffsetY = square.h;

	//fitting the loaded texture onto the grid
	mGrid->FitTextureOnGrid(square, columns, &mMapTexture->mTextureArea);

	mHoveredTile = -1;

	mStartTile = -1;
	mEndTile = -1;
	mHasSearched = true;
}

GameMap::~GameMap() {

	mGraphics = NULL;
	mInput = NULL;

	delete mMapTexture;
	mMapTexture = NULL;

	delete mGrid;
	mGrid = NULL;
}

//function to detect if mouse is within bounds of the constructed grid
bool GameMap::isMouseInGrid() {
	//if the input of the mouse is within bounds of the x/y of the constructed grid
	if (mInput->mMousePosX >= mGridMinX && mInput->mMousePosX <= mGridMaxX + mOffsetX
		&& mInput->mMousePosY >= mGridMinY && mInput->mMousePosY <= mGridMaxY + mOffsetY) {
		
		CalculateTileIndexFromMouse();
		return true;
	}
	else
		mHoveredTile = -1;

	return false;
}

//Our tiles are in a vector. here we mathmatically calculate the vector's index where the mouse is being hovered in. We pretty much get the square that is being collided with
void GameMap::CalculateTileIndexFromMouse() {
	//finding the index of the tile that is within the bounds of the position of the mouse
	mHoveredTile = ((mInput->mMousePosY - square.y) / square.h * mGrid->GetColumns()) + ((mInput->mMousePosX - square.x) / square.w);

	if (mInput->IsKeyHeld(SDL_SCANCODE_SPACE))
		mStartTile = mHoveredTile;
	if (mInput->IsKeyHeld(SDL_SCANCODE_TAB))
		mEndTile = mHoveredTile;
	if (mInput->IsKeyPressed(SDL_SCANCODE_BACKSPACE))
		mHasSearched = false;

}

std::vector<int> GameMap::BFS() {

	std::queue<int> explorationQueue;
	std::vector<int> parentTiles(mGrid->GetColumns() * mGrid->GetRows(), NULL);
	std::vector<bool> visitedTiles (mGrid->GetColumns() * mGrid->GetRows(), false);

	explorationQueue.push(mStartTile);
	visitedTiles[mStartTile] = true;

	int steps = 0;

	while (!explorationQueue.empty() && visitedTiles[mEndTile] == false) {

		int currentTile = explorationQueue.front();
		std::vector<int> neighbors{-1, -1, -1, -1};
		CalculateNeighbors(&currentTile, &neighbors[0], &neighbors[1], &neighbors[2], &neighbors[3]);

		printf("Exploring %d...\n", currentTile);
		//pushing neighbors to be explored
		for (int adjacentTile : neighbors) {

			if (adjacentTile >= 0 && adjacentTile < visitedTiles.size()) {

				if (!visitedTiles[adjacentTile] && !mGrid->mTiles[adjacentTile].mIsWall) {

					explorationQueue.push(adjacentTile);
					visitedTiles[adjacentTile] = true;
					parentTiles[adjacentTile] = currentTile;
				}
			}
		}
			
		explorationQueue.pop();
		printf("%d Popped!\n", currentTile);
		steps++;
	}

	printf("You went from %d to %d in %d number of steps!\n", mStartTile, mEndTile, steps);
	mHasSearched = true;

	PathFromBFS(parentTiles);

	return parentTiles;
}

std::vector<int> GameMap::BFS(int start, int finish) {

	std::queue<int> explorationQueue;
	std::vector<int> parentTiles(mGrid->GetColumns() * mGrid->GetRows(), NULL);
	std::vector<bool> visitedTiles(mGrid->GetColumns() * mGrid->GetRows(), false);

	explorationQueue.push(start);
	visitedTiles[start] = true;

	int steps = 0;

	while (!explorationQueue.empty() && visitedTiles[finish] == false) {

		int currentTile = explorationQueue.front();
		std::vector<int> neighbors{ -1, -1, -1, -1 };
		CalculateNeighbors(&currentTile, &neighbors[0], &neighbors[1], &neighbors[2], &neighbors[3]);

		//pushing neighbors to be explored
		for (int adjacentTile : neighbors) {

			if (adjacentTile >= 0 && adjacentTile < visitedTiles.size()) {

				if (!visitedTiles[adjacentTile] && !mGrid->mTiles[adjacentTile].mIsWall) {

					explorationQueue.push(adjacentTile);
					visitedTiles[adjacentTile] = true;
					parentTiles[adjacentTile] = currentTile;
				}
			}
		}

		explorationQueue.pop();
		steps++;
	}

	mHasSearched = true;

	return PathFromBFS(parentTiles, finish);
}

std::vector<int> GameMap::PathFromBFS(std::vector<int> parentTiles, int finish) {

	std::vector<int> path;
	for (int i = finish; i != NULL; i = parentTiles[i])
		path.push_back(i);

	std::reverse(path.begin(), path.end());

	return path;
}

std::vector<int> GameMap::PathFromBFS(std::vector<int> parentTiles) {

	std::vector<int> path;
	for (int i = mEndTile; i != NULL; i = parentTiles[i])
		path.push_back(i);

	std::reverse(path.begin(), path.end());

	return path;
}

void GameMap::CalculateNeighbors(int* currentTile, int* up, int* right, int* down, int* left) {

	*up = *currentTile - mGrid->GetColumns();
	*right = *currentTile + 1;
	*down = *currentTile + mGrid->GetColumns();
	*left = *currentTile - 1;
}

void GameMap::Update() {

	isMouseInGrid();
	if (!mHasSearched) {
		BFS();
		mHasSearched = true;
	}
		
}

void GameMap::Render() {
	//rendering the map via render method of texture class
	mMapTexture->Render();
	//drawing each grid space one by one
	for (auto tile : mGrid->mTiles)
		mGraphics->DrawGrid(tile.mTile);
	
	if(mHoveredTile != -1 && mHoveredTile < mGrid->mTiles.size())
		mGraphics->FillRectInGrid(mGrid->mTiles[mHoveredTile].mTile, 0, 255, 255, 0);

	if(mStartTile != -1)
		mGraphics->FillRectInGrid(mGrid->mTiles[mStartTile].mTile, 0, 255, 255, 0);
	if (mEndTile != -1)
		mGraphics->FillRectInGrid(mGrid->mTiles[mEndTile].mTile, 255, 0, 255, 0);
}