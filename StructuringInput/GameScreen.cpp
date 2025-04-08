#include "GameScreen.h"

GameScreen::GameScreen() {

	mGameMap = new GameMap;
	mPacMan = new PacManPlayer(mGameMap->square, mGameMap);
	mBlinky = new Ghost(mGameMap->square, mGameMap, "Blinky", mPacMan);
	mPinky = new Ghost(mGameMap->square, mGameMap, "Pinky", mPacMan);
	mInky = new Ghost(mGameMap->square, mGameMap, "Inky", mPacMan);
	mClyde = new Ghost(mGameMap->square, mGameMap, "Clyde", mPacMan);
	mInput = InputManager::Instance();
	mUI = new UI(mGameMap);

	mAllGhosts.push_back(mBlinky);
	mAllGhosts.push_back(mPinky);
	mAllGhosts.push_back(mInky);
	mAllGhosts.push_back(mClyde);

	mIsHit = false;
	mHasAte = true;
	mIsDying = false;
	mIsReady = false;
	mIsPlaying = true;
	mIsNextLevel = false;
	mMapAnimation = false;

	mTimer = Timer();

	mRoundScore = &mPacMan->mScore[0];
	mRoundNum = 1;
}

GameScreen::~GameScreen() {

	delete mGameMap;
	mGameMap = NULL;

	delete mPacMan;
	mPacMan = NULL;

	delete mBlinky;
	mBlinky = NULL;

	delete mPinky;
	mPinky = NULL;

	delete mInky;
	mInky = NULL;

	delete mClyde;
	mClyde = NULL;

	mInput = NULL;

	delete mUI;
	mUI = NULL;
}

void GameScreen::CollisionHandler() {
	
	for (auto ghost : mAllGhosts) {

		if (!mPacMan->mIsPoweredUp || !ghost->mIsEatable) {

			if (HasCollided(&mPacMan->mCollider, &ghost->mCollider)) {

				printf("Collided with: %s\n", ghost->mGhostName.c_str());
				mIsHit = true;
			}
		}
		else if(ghost->mIsEatable && !ghost->mIsDead){
			if (HasCollided(&mPacMan->mCollider, &ghost->mCollider)) {

				printf("Pac-Man ate: %s\n", ghost->mGhostName.c_str());
				ghost->mIsDead = true;
				printf("%d", ghost->mReturnedHome);
			}
		}
	}
}

void GameScreen::Update() {

	mGameMap->Update();

	if (!mIsHit) {

		if (mIsPlaying) {

			CollisionHandler();

			mPacMan->Update();

			mBlinky->Update();
			mPinky->Update();
			mInky->Update();
			mClyde->Update();

			mGameMap->Update();

			//reinitializing round score 245
			if (mRoundScore == NULL && mPacMan->mScore.size() % 2 != 0) 
				mRoundScore = &mPacMan->mScore[0];

			//checking if player completed level
			if (mRoundScore != NULL && mPacMan->mScore.size() % 2 == 0 && mIsPlaying) {

				mIsNextLevel = true;
				mRoundScore = 0;
			}

			mTimer.ResetTimer();

			if (mPacMan->mIsPoweredUp) {

				if (mAllGhosts[0]->mEatableTimer.DeltaTime() >= 10) {

					if (!mAllGhosts[0]->mIsEatable) {

						mPacMan->mIsPoweredUp = false;
					}
				}
			}
		}
	}

	else if (!mIsDying && !mIsReady){

		mIsPlaying = false;
		mBlinky->GameOver();
		mPinky->GameOver();
		mInky->GameOver();
		mClyde->GameOver();

		//enemy collider follow here
		mPacMan->mColliderEntity.FollowParent();

		mTimer.Update();

		if (mTimer.DeltaTime() > 1.5f) {

			mIsDying = true;
			mPacMan->SetDeathFrame();
		}
	}

	if (mIsNextLevel) {
		//printf("papa\n");
		//initiate animation stuff
		//reset positions
		//reset score
		//reset orbs
		mIsPlaying = false;

		mBlinky->GameOver();
		mPinky->GameOver();
		mInky->GameOver();
		mClyde->GameOver();

		mTimer.Update();

		if (mTimer.DeltaTime() > 1.0f) {

			mIsReady = true;
			mIsHit = true;
			mIsNextLevel = false;

			mRoundNum++;
			std::string roundUpdate = "Round " + std::to_string(mRoundNum);
			mUI->mRound->UpdateTextFont(roundUpdate, mUI->mFontColor);

			for (auto tile : mGameMap->mGrid->mTiles) {

				if (tile.mHasVisited) {
					printf("rrr\n");
					tile.mHasVisited = false;
					
				}
			}

			mGameMap->mGrid->SetNonOrbs();

			mTimer.ResetTimer();
		}
	}

	if (mIsDying) {

		if (!mPacMan->GameOver()) {

			mIsDying = false;
			mIsReady = true;

			mTimer.ResetTimer();
		}
	}

	if (mMapAnimation) {


	}

	if (mIsReady) {

		//printf("Ready?\n");

		mTimer.Update();

		mBlinky->Reset();
		mPinky->Reset();
		mInky->Reset();
		mClyde->Reset();
		//enemy collider reset here

		mPacMan->Reset();
		mPacMan->mColliderEntity.FollowParent();

		mUI->mIsRevealPlayerOne = true;
		mUI->mIsRevealReady = true;

		if (mUI->mIsRevealPlayerOne && mTimer.DeltaTime() >= 1.0) {

			mUI->mIsRevealPlayerOne = false;
			mIsHit = false;
		}
		if (mTimer.DeltaTime() >= 3.0) {

			mUI->mIsRevealReady = false;
			
			mIsReady = false;
			mIsPlaying = true;

			mRoundScore = NULL;
		}
	}

	//mUI->mScore 
	mUI->Update();
	
	std::string currentScore = std::to_string((mPacMan->mScore.size() - 1) * 10);

	if (mPacMan->mScore.size() != 0)
		mUI->mScore->UpdateTextFont(currentScore, mUI->mFontColor);
}

void GameScreen::Render() {

	mGameMap->Render();
	mPacMan->Render();

	if (!mIsDying && !mUI->mIsRevealPlayerOne) {

		mPinky->Render();
		mBlinky->Render();
		mInky->Render();
		mClyde->Render();
	}

	mUI->Render();
}