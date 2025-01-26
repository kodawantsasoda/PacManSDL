#include "PacManPlayer.h"

PacManPlayer::PacManPlayer(SDL_Rect moveSquare, GameMap* gameMap) {

	mInput = InputManager::Instance();

	mPacMan = new Texture("PMSpriteSheet.png");
	mPacMan->ClipLocalTexture(472, 0, 13, 15);

	mMoveSquare = moveSquare;
	mGameMap = gameMap;

	CurrentPositionOnGrid = 29;
	mScore.push_back(CurrentPositionOnGrid);

	startTicks = SDL_GetTicks();
	elapsedTicks = 0;
	deltaTime = 0.0f;

	mMoveSpeed = 3.0;
}

PacManPlayer::~PacManPlayer() {

	mInput = NULL;

	delete mPacMan;
	mPacMan = NULL;

	mGameMap = NULL;
}

void PacManPlayer::Move() {

	elapsedTicks = SDL_GetTicks() - startTicks;
	deltaTime = elapsedTicks * 0.001f;

	if (mIsMoving) {

		//moving in the positive direction: down or right
		if (mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x - mTargetTileX < 0) {
			//checking if the player moved to or past the target tile
			if (mPacMan->mTextureArea.x >= mTargetTileX) {

				//printf("Stopping");
				mIsMoving = false;
				CurrentPositionOnGrid++;
			}
		}
		
		else if (mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y - mTargetTileY < 0) {

			if (mPacMan->mTextureArea.y >= mTargetTileY) {

				printf("Stopping");
				mIsMoving = false;
				CurrentPositionOnGrid += mGameMap->mGrid->GetColumns();
			}
		}
		//moving in the negative direction: up or left
		else if (mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x - mTargetTileX > 0) {
			//checking if the player moved to or past the target tile
			if (mPacMan->mTextureArea.x <= mTargetTileX) {

				printf("Stopping");
				mIsMoving = false;
				CurrentPositionOnGrid--;
			}
		}

		else {
			//checking if the player moved to or past the target tile
			if (mPacMan->mTextureArea.y <= mTargetTileY) {

				printf("Stopping");
				mIsMoving = false;
				CurrentPositionOnGrid -= mGameMap->mGrid->GetColumns();
			}
		}
	}

	if (!mIsMoving) {

		mScore.push_back(CurrentPositionOnGrid);
		//Graphics::Instance()->FillRectInGrid(mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile, 0, 0, 0, 0);
	}

	else
		mPacMan->LerpTextureArea(mPacMan->mTextureArea.x, mPacMan->mTextureArea.y, mTargetTileX, mTargetTileY, deltaTime, mMoveSpeed);
}

void PacManPlayer::Update() {

	if (mIsMoving) {
		//finish moving...
		Move();
	}

	if (mInput->IsKeyPressed(SDL_SCANCODE_W) || mInput->IsKeyHeld(SDL_SCANCODE_W)) {

		if (mGameMap->mGrid->mTiles[CurrentPositionOnGrid - mGameMap->mGrid->GetColumns()].mIsWall)
			printf("WALLMOFO");
		
		else if (mIsMoving == false) {

			mIsMoving = true;
			mTargetTileX = mPacMan->mTextureArea.x;
			mTargetTileY = abs(mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y - mMoveSquare.h);
			startTicks = SDL_GetTicks();
			elapsedTicks = 0;
			deltaTime = 0.0f;
		}
	}

	if (mInput->IsKeyPressed(SDL_SCANCODE_A) || mInput->IsKeyHeld(SDL_SCANCODE_A)) {
		if (mGameMap->mGrid->mTiles[CurrentPositionOnGrid - 1].mIsWall)
			printf("WALLMOFO");

		else if (mIsMoving == false) {

			mIsMoving = true;
			mTargetTileX = abs(mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x - mMoveSquare.w);
			mTargetTileY = mPacMan->mTextureArea.y;
			startTicks = SDL_GetTicks();
			elapsedTicks = 0;
			deltaTime = 0.0f;
			//MoveRight();
		}
	}

	if (mInput->IsKeyPressed(SDL_SCANCODE_S) || mInput->IsKeyHeld(SDL_SCANCODE_S)) {

		if (mGameMap->mGrid->mTiles[CurrentPositionOnGrid + mGameMap->mGrid->GetColumns()].mIsWall)
			printf("WALLMOFO");

		else if (mIsMoving == false) {

			mIsMoving = true;
			mTargetTileX = mPacMan->mTextureArea.x;
			mTargetTileY = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y + mMoveSquare.h;
			startTicks = SDL_GetTicks();
			elapsedTicks = 0;
			deltaTime = 0.0f;
		}
	}

	if (mInput->IsKeyPressed(SDL_SCANCODE_D) || mInput->IsKeyHeld(SDL_SCANCODE_D)) {

		if (mGameMap->mGrid->mTiles[CurrentPositionOnGrid + 1].mIsWall)
			printf("WALLMOFO");

		else if(mIsMoving == false){

			mIsMoving = true;
			mTargetTileX = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x + mMoveSquare.w;
			mTargetTileY = mPacMan->mTextureArea.y;
			startTicks = SDL_GetTicks();
			elapsedTicks = 0;
			deltaTime = 0.0f;
			//MoveRight();
		}
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