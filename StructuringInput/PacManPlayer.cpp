#include "PacManPlayer.h"

PacManPlayer::PacManPlayer(SDL_Rect moveSquare, GameMap* gameMap) {

	mInput = InputManager::Instance();
	mMoveSquare = moveSquare;
	mGameMap = gameMap;

	mPacMan = new Texture("PMSpriteSheet.png");
	mPacMan->ClipLocalTexture(455, 0, 16, 16);
	mPacMan->PositionTextureArea(mGameMap->mGrid->mTiles[657].mTile.x - 8, mGameMap->mGrid->mTiles[657].mTile.y - 8);
	mPacMan->ScaleTextureArea(3, 8, 8);

	mTimer = Timer();

	mCollider = mPacMan->mTextureArea;
	mCollider.w -= 12;
	mCollider.h -= 12;
	mCollider.x = mPacMan->mTextureArea.x + (mPacMan->mTextureArea.w - mCollider.w) / 2;
	mCollider.y = mPacMan->mTextureArea.y + (mPacMan->mTextureArea.h - mCollider.h) / 2;

	mAnimator = new Animator(true, mPacMan, 2, 2, 0.05);
	mDeathAnimator = new Animator(true, mPacMan, 11, 0, 0.15);

	CurrentPositionOnGrid = 657;
	mScore.push_back(CurrentPositionOnGrid);

	mIsMoving = false;
	mCurrentInput = '0';

	mMoveSpeed = 7.5;
}

PacManPlayer::~PacManPlayer() {

	mInput = NULL;

	delete mPacMan;
	mPacMan = NULL;

	delete mAnimator;
	mAnimator = NULL;

	delete mDeathAnimator;
	mDeathAnimator = NULL;

	mGameMap = NULL;
}

//currently doesnt work exactly the way i want it to
int PacManPlayer::GetTileInFrontOfMouth() {

	switch (mCurrentInput) {

	case 'W':
		return CurrentPositionOnGrid - mGameMap->mGrid->GetColumns();
		break;
	case 'A':
		return CurrentPositionOnGrid - 1;
		break;
	case 'S':
		return CurrentPositionOnGrid + mGameMap->mGrid->GetColumns();
		break;
	case 'D':
		return CurrentPositionOnGrid + 1;
		break;
	default:
		return -1;
	}
}

void PacManPlayer::Move(char input) {

	mAnimator->Animate();

	mCollider.x = mPacMan->mTextureArea.x + (mPacMan->mTextureArea.w - mCollider.w) / 2;
	mCollider.y = mPacMan->mTextureArea.y + (mPacMan->mTextureArea.h - mCollider.h) / 2;

	mTimer.Update();

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
		mPacMan->LerpTextureArea(mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x - 8, mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y - 8, mTargetTileX, mTargetTileY, mTimer.DeltaTime(), mMoveSpeed);
}

bool PacManPlayer::GameOver() {

	if (!mDeathAnimator->mAnimationCycleComplete) {

		mDeathAnimator->Animate();
		return true;
	}
	else
		return false;
}

void PacManPlayer::SetDeathFrame() {

	mPacMan->mImageClip.x = XPOSDEATHCLIP;
	mDeathAnimator->Init(true, mPacMan, 11, 0, 0.15);
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
			mTargetTileX = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x - 8;
			mTargetTileY = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y - mMoveSquare.h - 8;
			break;
		case 'A':
			mTargetTileX = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x - mMoveSquare.w - 8;
			mTargetTileY = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y - 8;
			break;
		case 'S':
			mTargetTileX = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x - 8;
			mTargetTileY = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y + mMoveSquare.h - 8;
			break;
		case 'D':
			mTargetTileX = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.x + mMoveSquare.w - 8;
			mTargetTileY = mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile.y - 8;
			break;
		}

		mTimer.ResetTimer();
	}

	if (mInput->IsKeyPressed(SDL_SCANCODE_SPACE))
		printf("%d\n", CurrentPositionOnGrid);
}
//
void PacManPlayer::Render() {

	//if pac-man has collided with orb, we fill in the orb with a black square
	for (int i = 0; i < mScore.size(); i++) {

		Graphics::Instance()->FillRectInGrid(mGameMap->mGrid->mTiles[mScore[i]].mTile, 0, 0, 0, 0);
	}
	
	mPacMan->Render();

	/*COLLIDER DEBUGGING
	Graphics::Instance()->FillRectInGrid(mCollider, 255, 0, 0, 50);
	Graphics::Instance()->FillRectInGrid(mCollider, 255, 0, 0, 50);
	*/
}