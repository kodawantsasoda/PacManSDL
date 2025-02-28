#include "PacManPlayer.h"

PacManPlayer::PacManPlayer(SDL_Rect moveSquare, GameMap* gameMap) {

	mInput = InputManager::Instance();

	mPacMan = new Texture("PMSpriteSheet.png");
	mPacMan->ClipLocalTexture(489, 0, 13, 15);

	mMoveSquare = moveSquare;
	mGameMap = gameMap;

	CurrentPositionOnGrid = 29;
	mScore.push_back(CurrentPositionOnGrid);

	mIsMoving = false;
	mCurrentInput = '0';

	startTicks = SDL_GetTicks();
	elapsedTicks = 0;
	deltaTime = 0.0f;

	mMoveSpeed = 4.5;
}

PacManPlayer::~PacManPlayer() {

	mInput = NULL;

	delete mPacMan;
	mPacMan = NULL;

	mGameMap = NULL;
}

void PacManPlayer::ResetTimer() {

	startTicks = SDL_GetTicks();
	elapsedTicks = 0;
	deltaTime = 0.0f;
}

void PacManPlayer::Move(char input) {

	elapsedTicks = SDL_GetTicks() - startTicks;
	deltaTime = elapsedTicks * 0.001f;

	if (mPacMan->mTextureArea.x - mTargetTileX == 0 &&
		mPacMan->mTextureArea.y - mTargetTileY == 0) {

		mIsMoving = false;

		switch (input) {

		case 'W':
			CurrentPositionOnGrid -= mGameMap->mGrid->GetColumns();
			break;
		case 'A':
			CurrentPositionOnGrid--;
			break;
		case 'S':
			CurrentPositionOnGrid += mGameMap->mGrid->GetColumns();
			break;
		case 'D':
			CurrentPositionOnGrid++;
			break;
		}
	}

	if (!mIsMoving) 
		mScore.push_back(CurrentPositionOnGrid);

	else
		mPacMan->LerpTextureArea(mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x, mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y, mTargetTileX, mTargetTileY, deltaTime, mMoveSpeed);
}

void PacManPlayer::Update() {

	int nextTile = -1;

	if (mIsMoving) 
		Move(mCurrentInput);

	//only check input if pacman is not already moving
	if (!mIsMoving) {
		//determining the players next move based on input
		if (mInput->IsKeyPressed(SDL_SCANCODE_W) || mInput->IsKeyHeld(SDL_SCANCODE_W)) {

			nextTile = CurrentPositionOnGrid - mGameMap->mGrid->GetColumns();
			mCurrentInput = 'W';
		}

		else if (mInput->IsKeyPressed(SDL_SCANCODE_A) || mInput->IsKeyHeld(SDL_SCANCODE_A)) {

			nextTile = CurrentPositionOnGrid - 1;
			mCurrentInput = 'A';
		}

		else if (mInput->IsKeyPressed(SDL_SCANCODE_S) || mInput->IsKeyHeld(SDL_SCANCODE_S)) {

			nextTile = CurrentPositionOnGrid + mGameMap->mGrid->GetColumns();
			mCurrentInput = 'S';
		}

		else if (mInput->IsKeyPressed(SDL_SCANCODE_D) || mInput->IsKeyHeld(SDL_SCANCODE_D)) {

			nextTile = CurrentPositionOnGrid + 1;
			mCurrentInput = 'D';
		}
	}
	
	
	//if the requested tile on the map is NOT a wall
	if (nextTile != -1 && !mIsMoving && !mGameMap->mGrid->mTiles[nextTile].mIsWall) {

		mIsMoving = true;

		switch (mCurrentInput) {

		case 'W':
			mTargetTileX = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x;
			mTargetTileY = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y - mMoveSquare.h;
			break;
		case 'A':
			mTargetTileX = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x - mMoveSquare.w;
			mTargetTileY = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y;
			break;
		case 'S':
			mTargetTileX = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x;
			mTargetTileY = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y + mMoveSquare.h;
			break;
		case 'D':
			mTargetTileX = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x + mMoveSquare.w;
			mTargetTileY = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y;
			break;
		}

		ResetTimer();
	}

	if (mInput->IsKeyPressed(SDL_SCANCODE_SPACE))
		printf("%d\n", CurrentPositionOnGrid);
}
//
void PacManPlayer::Render() {

	for (int i = 0; i < mScore.size(); i++) {

		Graphics::Instance()->FillRectInGrid(mGameMap->mGrid->mTiles[mScore[i]].mTile, 0, 0, 0, 0);
	}
	
	mPacMan->Render();
}