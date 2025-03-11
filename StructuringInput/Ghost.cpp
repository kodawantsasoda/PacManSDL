
#include "Ghost.h"

Ghost::Ghost(SDL_Rect moveSquare, GameMap* gameMap, std::string name, PacManPlayer* pacMan) {

	mInput = InputManager::Instance();

	mGhost = new Texture("PMSpriteSheet.png");

	mTimer = Timer();

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

	mCurrentPositionOnGrid = 99;

	mMoveSpeed = 6.15;
	
	mPacManTile = 657;

	if(name == "Blinky")
		pathToPacMan = mGameMap->BFS(321, mPacManTile);
	else
		pathToPacMan = mGameMap->BFS(375, mPacManTile);

	mIt = 0;

	mIsMoving = false;

	mCollider = mGhost->mTextureArea;
	mCollider.w -= 12;
	mCollider.h -= 12;
	mCollider.x = mGhost->mTextureArea.x + (mGhost->mTextureArea.w - mCollider.w) / 2;
	mCollider.y = mGhost->mTextureArea.y + (mGhost->mTextureArea.h - mCollider.h) / 2;

	mColliderEntity.SetParent(&mCollider, &mGhost->mTextureArea);
}

Ghost::~Ghost() {

	mInput = NULL;

	delete mGhost;
	mGhost = NULL;

	mGameMap = NULL;

	mPacMan = NULL;
}

void Ghost::Move() {

	mColliderEntity.FollowParent();

	mTimer.Update();

	if (mIsMoving) {
		//moving in the positive direction: down or right
		if (mGhost->mTextureArea.x - mTargetTileX == 0 &&
			mGhost->mTextureArea.y - mTargetTileY == 0) {

			mIsMoving = false;
			mCurrentPositionOnGrid = pathToPacMan[mIt];
		}
	}

	if (mIsMoving)
		mGhost->LerpTextureArea(mGameMap->mGrid->mTiles[pathToPacMan[mIt - 1]].mTile.x - mPacMan->OFFSETTEXTURE, 
								mGameMap->mGrid->mTiles[pathToPacMan[mIt - 1]].mTile.y - mPacMan->OFFSETTEXTURE, 
								mTargetTileX, mTargetTileY, mTimer.DeltaTime(), mMoveSpeed);
}

void Ghost::GameOver() {

	mAnimator->Animate();
}

void Ghost::Reset() {

	if (mGhostName == "Blinky") {

		pathToPacMan = (mGameMap->BFS(321, mPacManTile));
		mGhost->PositionTextureArea(mGameMap->mGrid->mTiles[321].mTile.x, mGameMap->mGrid->mTiles[321].mTile.y);
		mCurrentPositionOnGrid = 321;
	}
	else if (mGhostName == "Pinky") {

		pathToPacMan = (mGameMap->BFS(375, mPacManTile));
		mGhost->PositionTextureArea(mGameMap->mGrid->mTiles[375].mTile.x, mGameMap->mGrid->mTiles[375].mTile.y);
		mCurrentPositionOnGrid = 375;
	}

	mIt = 0;
	mIsMoving = false;
}

void Ghost::Update() {

	mAnimator->Animate();

	mPacManTile = mPacMan->mCurrentPositionOnGrid;

	if (mCurrentPositionOnGrid != pathToPacMan[pathToPacMan.size() - 1]) {

		if (mIsMoving == false) {

			mIt++;
			mIsMoving = true;
			mTargetTileX = mGameMap->mGrid->mTiles[pathToPacMan[mIt]].mTile.x - mPacMan->OFFSETTEXTURE;
			mTargetTileY = mGameMap->mGrid->mTiles[pathToPacMan[mIt]].mTile.y - mPacMan->OFFSETTEXTURE;

			mTimer.ResetTimer();
		}
		else
			Move();
	}

	if (mIsMoving == false && pathToPacMan[pathToPacMan.size() - 1] != mPacManTile) {

		int finalTile = mPacManTile;
		mIt = 0;

		if(mGhostName == "Blinky")
			pathToPacMan = mGameMap->BFS(mCurrentPositionOnGrid, finalTile);
		else {
			if (!mGameMap->mGrid->mTiles[mPacMan->GetTileInFrontOfMouth()].mIsWall) {

				pathToPacMan = mGameMap->BFS(mCurrentPositionOnGrid, mPacMan->GetTileInFrontOfMouth());
			}
			else
				pathToPacMan = mGameMap->BFS(mCurrentPositionOnGrid, finalTile);
		}
	}
}

//
void Ghost::Render() {

	mGhost->Render();
	//Graphics::Instance()->FillRectInGrid(mCollider, 255, 0, 0, 50);
}