#include "PacManPlayer.h"

PacManPlayer::PacManPlayer(SDL_Rect moveSquare, GameMap* gameMap) {

	mInput = InputManager::Instance();
	mMoveSquare = moveSquare;
	mGameMap = gameMap;

	mPacMan = new Texture("PMSpriteSheet.png");
	mPacMan->ClipLocalTexture(455, 0, 16, 16);
	mPacMan->PositionTextureArea(mGameMap->mGrid->mTiles[657].mTile.x - OFFSETTEXTURE, mGameMap->mGrid->mTiles[657].mTile.y - OFFSETTEXTURE);
	mPacMan->ScaleTextureArea(3, 8, 8);

	mTimer = Timer();
	mPowerUpTimer = Timer();

	mCollider = mPacMan->mTextureArea;
	mCollider.w -= 12;
	mCollider.h -= 12;
	mCollider.x = mPacMan->mTextureArea.x + (mPacMan->mTextureArea.w - mCollider.w) / 2;
	mCollider.y = mPacMan->mTextureArea.y + (mPacMan->mTextureArea.h - mCollider.h) / 2;

	mColliderEntity.SetParent(&mCollider, &mPacMan->mTextureArea);

	mAnimator = new Animator(true, mPacMan, 2, 2, 0.05);
	mDeathAnimator = new Animator(true, mPacMan, 11, 0, 0.15);

	mCurrentPositionOnGrid = 657;
	mScore.push_back(mCurrentPositionOnGrid);

	mIsMoving = false;
	mCurrentInput = '0';

	mMoveSpeed = 7.0;

	mIsPoweredUp = false;
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
		return mCurrentPositionOnGrid - mGameMap->mGrid->GetColumns();
		break;
	case 'A':
		return mCurrentPositionOnGrid - 1;
		break;
	case 'S':
		return mCurrentPositionOnGrid + mGameMap->mGrid->GetColumns();
		break;
	case 'D':
		return mCurrentPositionOnGrid + 1;
		break;
	default:
		return -1;
	}
}

void PacManPlayer::Move(char input) {

	mAnimator->Animate();

	/*mCollider.x = mPacMan->mTextureArea.x + (mPacMan->mTextureArea.w - mCollider.w) / 2;
	mCollider.y = mPacMan->mTextureArea.y + (mPacMan->mTextureArea.h - mCollider.h) / 2;*/

	mColliderEntity.FollowParent();

	mTimer.Update();

	if (mPacMan->mTextureArea.x - mTargetTileX == 0 &&
		mPacMan->mTextureArea.y - mTargetTileY == 0) {

		mIsMoving = false;

		switch (input) {

		case 'W':
			mCurrentPositionOnGrid -= mGameMap->mGrid->GetColumns();
			break;
		case 'A':
			mCurrentPositionOnGrid--;
			break;
		case 'S':
			mCurrentPositionOnGrid += mGameMap->mGrid->GetColumns();
			break;
		case 'D':
			mCurrentPositionOnGrid++;
			break;
		}
	}

	if (!mIsMoving && !mGameMap->mGrid->mTiles[mCurrentPositionOnGrid].mHasVisited) {

		mScore.push_back(mCurrentPositionOnGrid);
		mGameMap->mGrid->mTiles[mCurrentPositionOnGrid].mHasVisited = true;
	}

	else
		mPacMan->LerpTextureArea(mGameMap->mGrid->mTiles[mCurrentPositionOnGrid].mTile.x - OFFSETTEXTURE, 
								mGameMap->mGrid->mTiles[mCurrentPositionOnGrid].mTile.y - OFFSETTEXTURE, 
								mTargetTileX, mTargetTileY, mTimer.DeltaTime(), mMoveSpeed);
}

void PacManPlayer::Reset() {

	mIsMoving = false;
	mCurrentPositionOnGrid = 657;
	mPacMan->PositionTextureArea(mGameMap->mGrid->mTiles[657].mTile.x, mGameMap->mGrid->mTiles[657].mTile.y - OFFSETTEXTURE);
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

			nextTile = mCurrentPositionOnGrid - mGameMap->mGrid->GetColumns();
			mCurrentInput = 'W';
		}

		else if (mInput->IsKeyPressed(SDL_SCANCODE_A) || mInput->IsKeyHeld(SDL_SCANCODE_A)) {

			nextTile = mCurrentPositionOnGrid - 1;
			mCurrentInput = 'A';
		}

		else if (mInput->IsKeyPressed(SDL_SCANCODE_S) || mInput->IsKeyHeld(SDL_SCANCODE_S)) {

			nextTile = mCurrentPositionOnGrid + mGameMap->mGrid->GetColumns();
			mCurrentInput = 'S';
		}

		else if (mInput->IsKeyPressed(SDL_SCANCODE_D) || mInput->IsKeyHeld(SDL_SCANCODE_D)) {

			nextTile = mCurrentPositionOnGrid + 1;
			mCurrentInput = 'D';
		}
	}
	
	//if the requested tile on the map is NOT a wall
	if (nextTile != -1 && !mIsMoving && !mGameMap->mGrid->mTiles[nextTile].mIsWall) {

		mIsMoving = true;

		switch (mCurrentInput) {

		case 'W':
			mTargetTileX = mGameMap->mGrid->mTiles[mCurrentPositionOnGrid].mTile.x - OFFSETTEXTURE;
			mTargetTileY = mGameMap->mGrid->mTiles[mCurrentPositionOnGrid].mTile.y - mMoveSquare.h - OFFSETTEXTURE;
			break;
		case 'A':
			mTargetTileX = mGameMap->mGrid->mTiles[mCurrentPositionOnGrid].mTile.x - mMoveSquare.w - OFFSETTEXTURE;
			mTargetTileY = mGameMap->mGrid->mTiles[mCurrentPositionOnGrid].mTile.y - OFFSETTEXTURE;
			break;
		case 'S':
			mTargetTileX = mGameMap->mGrid->mTiles[mCurrentPositionOnGrid].mTile.x - OFFSETTEXTURE;
			mTargetTileY = mGameMap->mGrid->mTiles[mCurrentPositionOnGrid].mTile.y + mMoveSquare.h - OFFSETTEXTURE;
			break;
		case 'D':
			mTargetTileX = mGameMap->mGrid->mTiles[mCurrentPositionOnGrid].mTile.x + mMoveSquare.w - OFFSETTEXTURE;
			mTargetTileY = mGameMap->mGrid->mTiles[mCurrentPositionOnGrid].mTile.y - OFFSETTEXTURE;
			break;
		}

		mTimer.ResetTimer();
	}

	if (mCurrentPositionOnGrid == 670) {

		mIsPoweredUp = true;
		printf("POWER-UP\n");
	}

	if (mInput->IsKeyPressed(SDL_SCANCODE_SPACE))
		printf("%d\n", mCurrentPositionOnGrid);
}
//
void PacManPlayer::Render() {

	//if pac-man has collided with orb, we fill in the orb with a black square
	for (int i = 0; i < mScore.size(); i++) {

		Graphics::Instance()->FillRectInGrid(mGameMap->mGrid->mTiles[mScore[i]].mTile, 0, 0, 0, 0);
	}
	
	mPacMan->Render();

	//COLLIDER DEBUGGING
	//Graphics::Instance()->FillRectInGrid(mCollider, 255, 0, 0, 50);
}