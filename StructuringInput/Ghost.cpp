
#include "Ghost.h"

Ghost::Ghost(SDL_Rect moveSquare, GameMap* gameMap, std::string name, PacManPlayer* pacMan) {

	mInput = InputManager::Instance();

	mGhost = new Texture("PMSpriteSheet.png");

	if(name == "Blinky")
		mGhost->ClipLocalTexture(489, 65, 16, 16);
	else
		mGhost->ClipLocalTexture(489, 80, 16, 16);

	mAnimator = new Animator(true, mGhost, 1, 0, 0.1);

	mGhost->ScaleTextureArea(3, 10, 10);

	mGhostName = name;

	mMoveSquare = moveSquare;
	mGameMap = gameMap;
	mPacMan = pacMan;

	CurrentPositionOnGrid = 99;

	startTicks = SDL_GetTicks();
	elapsedTicks = 0;
	deltaTime = 0.0f;

	mMoveSpeed = 1.0;
	
	mPacManTile = 657;

	if(name == "Blinky")
		pathToPacMan = mGameMap->BFS(321, mPacManTile);
	else
		pathToPacMan = mGameMap->BFS(400, mPacManTile);

	mIt = 0;

	mIsMoving = false;

	mCollider = mGhost->mTextureArea;
	mCollider.w -= 12;
	mCollider.h -= 12;
	mCollider.x = mGhost->mTextureArea.x + (mGhost->mTextureArea.w - mCollider.w) / 2;
	mCollider.y = mGhost->mTextureArea.y + (mGhost->mTextureArea.h - mCollider.h) / 2;
}

Ghost::~Ghost() {

	mInput = NULL;

	delete mGhost;
	mGhost = NULL;

	mGameMap = NULL;

	mPacMan = NULL;
}

void Ghost::Move() {

	mCollider.x = mGhost->mTextureArea.x + (mGhost->mTextureArea.w - mCollider.w) / 2;
	mCollider.y = mGhost->mTextureArea.y + (mGhost->mTextureArea.h - mCollider.h) / 2;

	elapsedTicks = SDL_GetTicks() - startTicks;
	deltaTime = elapsedTicks * 0.001f;
	if (mIsMoving) {
		//moving in the positive direction: down or right
		if (mGhost->mTextureArea.x - mTargetTileX == 0 &&
			mGhost->mTextureArea.y - mTargetTileY == 0) {

			mIsMoving = false;
			CurrentPositionOnGrid = pathToPacMan[mIt];
		}
	}

	if (mIsMoving)
		mGhost->LerpTextureArea(mGameMap->mGrid->mTiles[pathToPacMan[mIt - 1]].mTile.x - 8, mGameMap->mGrid->mTiles[pathToPacMan[mIt - 1]].mTile.y - 8, mTargetTileX, mTargetTileY, deltaTime, mMoveSpeed);
}

void Ghost::GameOver() {

	mAnimator->Animate();
}

void Ghost::Update() {

	mAnimator->Animate();

	mPacManTile = mPacMan->CurrentPositionOnGrid;

	if (CurrentPositionOnGrid != pathToPacMan[pathToPacMan.size() - 1]) {

		if (mIsMoving == false) {

			mIt++;
			mIsMoving = true;
			mTargetTileX = mGameMap->mGrid->mTiles[pathToPacMan[mIt]].mTile.x - 8;
			mTargetTileY = mGameMap->mGrid->mTiles[pathToPacMan[mIt]].mTile.y - 8;
			startTicks = SDL_GetTicks();
			elapsedTicks = 0;
			deltaTime = 0.0f;
		}
		else
			Move();
	}

	if (mIsMoving == false && pathToPacMan[pathToPacMan.size() - 1] != mPacManTile) {

		int finalTile = mPacManTile;
		mIt = 0;

		if(mGhostName == "Blinky")
			pathToPacMan = mGameMap->BFS(CurrentPositionOnGrid, finalTile);
		else {
			if (!mGameMap->mGrid->mTiles[mPacMan->GetTileInFrontOfMouth()].mIsWall) {

				pathToPacMan = mGameMap->BFS(CurrentPositionOnGrid, mPacMan->GetTileInFrontOfMouth());
			}
			else
				pathToPacMan = mGameMap->BFS(CurrentPositionOnGrid, finalTile);
		}
	}
}

//
void Ghost::Render() {

	mGhost->Render();
	Graphics::Instance()->FillRectInGrid(mCollider, 255, 0, 0, 50);
}