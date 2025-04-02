
#include "Ghost.h"

Ghost::Ghost(SDL_Rect moveSquare, GameMap* gameMap, std::string name, PacManPlayer* pacMan) {

	mInput = InputManager::Instance();

	mGhost = new Texture("PMSpriteSheet.png");

	mTimer = Timer();
	mWaveTimer = Timer();
	mEatableTimer = Timer();

	mGhostName = name;

	SpriteClipGhosts();

	mAnimator = new Animator(true, mGhost, 1, 0, 0.1);

	mMoveSquare = moveSquare;
	mGameMap = gameMap;
	mPacMan = pacMan;

	mCurrentPositionOnGrid = 99;

	mMoveSpeed = 5.0;
	mNormalSpeed = 5.0;
	mChaseSpeed = 7.0;
	mDeadSpeed = 10.0;
	
	mPacManTile = 657;

	if(name == "Blinky")
		pathToPacMan = mGameMap->BFS(321, mPacManTile);
	else if(name == "Pinky")
		pathToPacMan = mGameMap->BFS(375, mPacManTile);
	else if (name == "Inky")
		pathToPacMan = mGameMap->BFS(377, mPacManTile);
	else if (name == "Clyde")
		pathToPacMan = mGameMap->BFS(379, mPacManTile);

	mIt = 0;
	mPatternIterator = 0;

	mIsMoving = false;
	mIsEndWave = true;
	mIsEatable = false;
	mIsDead = false;
	mReturnedHome = false;

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

void Ghost::SpriteClipGhosts() {

	if (mGhostName == "Blinky")
		mGhost->ClipLocalTexture(488, 64, 16, 16);
	else if (mGhostName == "Pinky")
		mGhost->ClipLocalTexture(488, 80, 16, 16);
	else if (mGhostName == "Inky")
		mGhost->ClipLocalTexture(488, 96, 16, 16);
	else if (mGhostName == "Clyde")
		mGhost->ClipLocalTexture(488, 112, 16, 16);

	mGhost->ScaleTextureArea(3, 10, 10);
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
	else if (mGhostName == "Inky") {

		pathToPacMan = (mGameMap->BFS(377, mPacManTile));
		mGhost->PositionTextureArea(mGameMap->mGrid->mTiles[377].mTile.x, mGameMap->mGrid->mTiles[377].mTile.y);
		mCurrentPositionOnGrid = 377;
	}
	else if (mGhostName == "Clyde") {

		pathToPacMan = (mGameMap->BFS(379, mPacManTile));
		mGhost->PositionTextureArea(mGameMap->mGrid->mTiles[379].mTile.x, mGameMap->mGrid->mTiles[379].mTile.y);
		mCurrentPositionOnGrid = 379;
	}

	mIt = 0;
	mIsMoving = false;
}

void Ghost::Move() {

	if (pathToPacMan.size() <= 5 && !mIsEndWave) {

		mMoveSpeed = mChaseSpeed;
	}

	else if (mIsDead) {

		mMoveSpeed = mDeadSpeed;
	}

	else if(mMoveSpeed != mNormalSpeed){

		mMoveSpeed = mNormalSpeed;
	}

	mColliderEntity.FollowParent();

	mTimer.Update();
	mWaveTimer.Update();

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

void Ghost::Wave() {

	if (!mIsEndWave && mWaveTimer.DeltaTime() >= 10.0) {

		mIsEndWave = !mIsEndWave;
		mWaveTimer.ResetTimer();
	}

	if (pathToPacMan.size() == 1) {

		if (mPatternIterator == BLINKYPATTERN.size() - 1) {
			
			mPatternIterator = 0;
			mIsEndWave = false;
			mWaveTimer.ResetTimer();
		}
		else
			mPatternIterator++;
	}
}

void Ghost::HandleEatState() {

	if (mReturnedHome) {

		if (!mPacMan->mIsPoweredUp) {

			mReturnedHome = false;
		}
	}

	else if (mPacMan->mIsPoweredUp && !mIsEatable) {

		//ensures only to be performed once so the animator can animate properly
		mIsEatable = true;

		mGhost->mImageClip.x = 584;
		mGhost->mImageClip.y = 64;

		//reinitialize animator so we can have the ghost change to the in danger animation
		mAnimator->Init(true, mGhost, 1, 0, 0.1);

		mEatableTimer.ResetTimer();
	}

	else if (mPacMan->mIsPoweredUp && mEatableTimer.DeltaTime() < 10) {

		//only update timer when these conditions are satisfied
		mEatableTimer.Update();

		//change animation to white... 3 seconds left until changing out of the eatable state
		if (mEatableTimer.DeltaTime() >= 7 && !mIsChanging) {

			mIsChanging = true;

			mGhost->mImageClip.x = 600;
			mGhost->mImageClip.y = 64;

			//reinitialize animator so we can have the ghost change to the in danger animation
			mAnimator->Init(true, mGhost, 1, 0, 0.15);
		}
	}
	else if (mEatableTimer.DeltaTime() >= 10) {

		printf("%s switched off\n", mGhostName.c_str());

		mPacMan->mIsPoweredUp = false;

		printf("are we ever here?\n");
		mIsEatable = false;
		mIsChanging = false;

		//mPacMan->mIsPoweredUp = false;

		//reset timer for later use
		mEatableTimer.ResetTimer();

		SpriteClipGhosts();
		mAnimator = new Animator(true, mGhost, 1, 0, 0.1);
	}
}

void Ghost::ReturnHome() {


	pathToPacMan = mGameMap->BFS(mCurrentPositionOnGrid, 377);

	if (mGhost->mImageClip.x != 584 && mGhost->mImageClip.y != 80) {

		mGhost->mImageClip.x = 584;
		mGhost->mImageClip.y = 80;

		//reinitialize animator so we can have the ghost change to the in danger animation
		mAnimator->Init(true, mGhost, 1, 0, 0.1);
	}
}

void Ghost::Update() {

	mAnimator->Animate();

	//Wave attacks and dispersing
	mWaveTimer.Update();
	Wave();

	//if(!mReturnedHome)
		//handling checking for changing ghost behavior when pacman eats the power up orb
		HandleEatState();

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

	if (!mIsMoving) {

		int finalTile = mPacManTile;
		mIt = 0;


		if (mIsDead) {

			ReturnHome();

			if (mCurrentPositionOnGrid == pathToPacMan[pathToPacMan.size() - 1]) {

				mIsDead = false;
				mIsEatable = false;
				mIsChanging = false;
				mReturnedHome = true;

				//reset timer for later use
				mEatableTimer.ResetTimer();

				SpriteClipGhosts();
				mAnimator = new Animator(true, mGhost, 1, 0, 0.1);
			}
		}
		//Enemy positions for when they arent attacking pacman (End of wave)
		else if (mIsEndWave && !mIsEatable) {
			
			if (mGhostName == "Blinky") {

				pathToPacMan = mGameMap->BFS(mCurrentPositionOnGrid, BLINKYPATTERN[mPatternIterator]);
				//printf("%s traveling to tile %d\n", mGhostName.c_str(), BLINKYPATTERN[mPatternIterator]);
			}
			else if (mGhostName == "Pinky") {

				pathToPacMan = mGameMap->BFS(mCurrentPositionOnGrid, PINKYPATTERN[mPatternIterator]);
				//printf("%s traveling to tile %d\n", mGhostName.c_str(), PINKYPATTERN[mPatternIterator]);
			}
			else if (mGhostName == "Inky") {

				pathToPacMan = mGameMap->BFS(mCurrentPositionOnGrid, INKYPATTERN[mPatternIterator]);
				//printf("%s traveling to tile %d\n", mGhostName.c_str(), INKYPATTERN[mPatternIterator]);
			}
			else if (mGhostName == "Clyde") {

				pathToPacMan = mGameMap->BFS(mCurrentPositionOnGrid, CLYDEPATTERN[mPatternIterator]);
				//printf("%s traveling to tile %d\n", mGhostName.c_str(), CLYDEPATTERN[mPatternIterator]);
			}
		}

		//maybe i should determine what quad pacman is in, and then go from there
		else if (mIsEatable) {
			
			int quad1 = abs(mPacManTile - 85);
			int quad2 = abs(mPacManTile - 110);
			int quad3 = abs(mPacManTile - 645);
			int quad4 = abs(mPacManTile - 670);

			int max = std::max({ quad1, quad2, quad3, quad4 });

			if (max == quad1) {

				pathToPacMan = mGameMap->BFS(mCurrentPositionOnGrid, 85);
			}
			else if (max == quad2) {

				pathToPacMan = mGameMap->BFS(mCurrentPositionOnGrid, 110);
			}
			else if (max == quad3) {

				pathToPacMan = mGameMap->BFS(mCurrentPositionOnGrid, 645);
			}
			else if (max == quad4) {

				pathToPacMan = mGameMap->BFS(mCurrentPositionOnGrid, 670);
			}
		}

		//ATTACK PAC MAN!
		else {
			pathToPacMan = mGameMap->BFS(mCurrentPositionOnGrid, finalTile);
		}
	}
}

//
void Ghost::Render() {

	mGhost->Render();
	//Graphics::Instance()->FillRectInGrid(mCollider, 255, 0, 0, 50);
}