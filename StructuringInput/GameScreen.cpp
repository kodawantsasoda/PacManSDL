#include "GameScreen.h"

GameScreen::GameScreen() {

	mGameMap = new GameMap;
	mPacMan = new PacManPlayer(mGameMap->square, mGameMap);
	mBlinky = new Ghost(mGameMap->square, mGameMap, "Blinky", mPacMan);
	mPinky = new Ghost(mGameMap->square, mGameMap, "Pinky", mPacMan);
	mInput = InputManager::Instance();
	mUI = new UI(mGameMap);

	mAllGhosts.push_back(mBlinky);
	mAllGhosts.push_back(mPinky);

	mIsHit = false;
	mIsDying = false;
	mIsReady = false;
	mIsPlaying = true;

	mTimer = Timer();
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

	mInput = NULL;

	delete mUI;
	mUI = NULL;
}

void GameScreen::CollisionHandler() {
	
	for (auto ghost : mAllGhosts) {

		if (HasCollided(&mPacMan->mCollider, &ghost->mCollider)) {

			printf("Collided with: %s\n", ghost->mGhostName.c_str());
			mIsHit = true;
		}
	}
}

void GameScreen::Update() {

	if (!mIsHit) {

		if (mIsPlaying) {
			mPacMan->Update();

			mBlinky->Update();
			mPinky->Update();

			mGameMap->Update();

			CollisionHandler();

			mTimer.ResetTimer();
		}
	}

	else if (!mIsDying && !mIsReady){

		mIsPlaying = false;
		mBlinky->GameOver();
		mPinky->GameOver();

		//enemy collider follow here
		mPacMan->mColliderEntity.FollowParent();

		mTimer.Update();

		if (mTimer.DeltaTime() > 1.5f) {
			mIsDying = true;
			mPacMan->SetDeathFrame();
		}
	}

	if (mIsDying) {

		if (!mPacMan->GameOver()) {

			mIsDying = false;
			mIsReady = true;

			mTimer.ResetTimer();
		}
	}

	if (mIsReady) {

		mTimer.Update();

		mBlinky->Reset();
		mPinky->Reset();
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
		}
	}

	mUI->Update();
}

void GameScreen::Render() {

	mGameMap->Render();
	mPacMan->Render();

	if (!mIsDying && !mUI->mIsRevealPlayerOne) {

		mPinky->Render();
		mBlinky->Render();
	}

	mUI->Render();
}