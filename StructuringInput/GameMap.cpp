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
}

void GameMap::Update() {

	isMouseInGrid();
}

void GameMap::Render() {
	//rendering the map via render method of texture class
	mMapTexture->Render();
	//drawing each grid space one by one
	for (auto tile : mGrid->mTiles)
		//mGraphics->DrawGrid(tile.mTile);
	
	if(mHoveredTile != -1 && mHoveredTile < mGrid->mTiles.size())
		mGraphics->FillRectInGrid(mGrid->mTiles[mHoveredTile].mTile, 0, 255, 255, 0);
}