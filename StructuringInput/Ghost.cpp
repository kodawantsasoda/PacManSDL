
#include "Ghost.h"

Ghost::Ghost(SDL_Rect moveSquare, GameMap* gameMap) {

	mInput = InputManager::Instance();

	mGhost = new Texture("PMSpriteSheet.png");
	mGhost->ClipLocalTexture(472, 65, 15, 15);

	mMoveSquare = moveSquare;
	mGameMap = gameMap;

	CurrentPositionOnGrid = 99;

	startTicks = SDL_GetTicks();
	elapsedTicks = 0;
	deltaTime = 0.0f;

	mMoveSpeed = 6.0;
	
	mPacManTile = 29;
	pathToPacMan = mGameMap->BFS(99, mPacManTile);

	mIt = 0;

	mIsMoving = false;
}

Ghost::~Ghost() {

	mInput = NULL;

	delete mGhost;
	mGhost = NULL;

	mGameMap = NULL;
}

void Ghost::Move() {

	elapsedTicks = SDL_GetTicks() - startTicks;
	deltaTime = elapsedTicks * 0.001f;
	if (mIsMoving) {
		//moving in the positive direction: down or right
		if (mGhost->mTextureArea.x - mTargetTileX == 0 &&
			mGhost->mTextureArea.y - mTargetTileY == 0) {

			//printf("Stopping");
			mIsMoving = false;
			CurrentPositionOnGrid = pathToPacMan[mIt];
		}
	}

	if (mIsMoving)
		mGhost->LerpTextureArea(mGameMap->mGrid->mTiles[pathToPacMan[mIt - 1]].mTile.x, mGameMap->mGrid->mTiles[pathToPacMan[mIt - 1]].mTile.y, mTargetTileX, mTargetTileY, deltaTime, mMoveSpeed);
}

void Ghost::Update() {

	if (CurrentPositionOnGrid != pathToPacMan[pathToPacMan.size() - 1]) {

		if (mIsMoving == false) {

			mIt++;
			mIsMoving = true;
			mTargetTileX = mGameMap->mGrid->mTiles[pathToPacMan[mIt]].mTile.x;
			mTargetTileY = mGameMap->mGrid->mTiles[pathToPacMan[mIt]].mTile.y;
			//printf("\n%d\n", pathToPacMan[mIt]);
			//printf("%d %d\n", mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y, mTargetTileY);
			startTicks = SDL_GetTicks();
			elapsedTicks = 0;
			deltaTime = 0.0f;
		}
		else {
			Move();
		}
	}

	if (mIsMoving == false && pathToPacMan[pathToPacMan.size() - 1] != mPacManTile) {

		mIt = 0;
		pathToPacMan = mGameMap->BFS(CurrentPositionOnGrid, mPacManTile);
	}
}

//
void Ghost::Render() {


	mGhost->Render();
}