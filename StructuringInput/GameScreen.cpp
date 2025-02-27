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

	StageEntities();

	mIsHit = false;
	mIsDying = false;
	mIsReady = false;
	mIsPlaying = true;

	startTicks = SDL_GetTicks();
	elapsedTicks = 0;
	deltaTime = 0.0f;
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

void GameScreen::StageEntities() {

	//scaling and positioning pacman
	int pacXOffset = 0, pacYOffset = 3;
	//mPacMan->mPacMan->PositionTextureArea(mGameMap->mGrid->mTiles[29].mTile.x, mGameMap->mGrid->mTiles[29].mTile.y);
	//mPacMan->mPacMan->ScaleTextureArea(2, 0, 0);

	mBlinky->mGhost->PositionTextureArea(mGameMap->mGrid->mTiles[321].mTile.x - pacXOffset, mGameMap->mGrid->mTiles[321].mTile.y - pacYOffset);
	//mBlinky->mGhost->ScaleTextureArea(2, 0, 0);

	mPinky->mGhost->PositionTextureArea(mGameMap->mGrid->mTiles[375].mTile.x - pacXOffset, mGameMap->mGrid->mTiles[375].mTile.y - pacYOffset);
	//mPinky->mGhost->ScaleTextureArea(2, 0, 0);

	//can pacnan move to this square?
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
			mBlinky->mPacManTile = mPacMan->CurrentPositionOnGrid;

			mPinky->Update();
			mPinky->mPacManTile = mPacMan->CurrentPositionOnGrid;

			mGameMap->Update();

			CollisionHandler();

			startTicks = SDL_GetTicks();
			elapsedTicks = 0;
			deltaTime = 0.0f;
		}
	}

	else if (!mIsDying && !mIsReady){

		mIsPlaying = false;
		mBlinky->GameOver();
		mPinky->GameOver();

		mPacMan->mCollider.x = mPacMan->mPacMan->mTextureArea.x + (mPacMan->mPacMan->mTextureArea.w - mPacMan->mCollider.w) / 2;
		mPacMan->mCollider.y = mPacMan->mPacMan->mTextureArea.y + (mPacMan->mPacMan->mTextureArea.h - mPacMan->mCollider.h) / 2;

		elapsedTicks = SDL_GetTicks() - startTicks;
		deltaTime = elapsedTicks * 0.001f;

		if (deltaTime > 1.5f) {
			mIsDying = true;
			printf("\n2 seconds past!\n");
			mPacMan->SetDeathFrame();
		}


		//halt ghosts -- check
		// halt pacman -- check
		// wait a second -- check
		// clear ghosts -- check
		// animateion death -- check
		// place ghosts and pacman at starting -- check
		// ready timer
		//change game state
		/*
		mIsHit = false;

		
		StageEntities();
		mBlinky->pathToPacMan = (mGameMap->BFS(99, mBlinky->mPacManTile));
		mBlinky->mIt = 0;
		mBlinky->mIsMoving = false;
		mBlinky->CurrentPositionOnGrid = 99;
		mPinky->pathToPacMan = (mGameMap->BFS(400, mPinky->mPacManTile));
		mPinky->mIt = 0;
		mPinky->mIsMoving = false;
		mPinky->CurrentPositionOnGrid = 400;
		*/
	}

	if (mIsDying) {

		if (!mPacMan->GameOver()) {

			mIsDying = false;
			mIsReady = true;

			startTicks = SDL_GetTicks();
			elapsedTicks = 0;
			deltaTime = 0.0f;
		}
	}

	if (mIsReady) {

		elapsedTicks = SDL_GetTicks() - startTicks;
		deltaTime = elapsedTicks * 0.001f;

		StageEntities();

		mBlinky->pathToPacMan = (mGameMap->BFS(321, mBlinky->mPacManTile));
		mBlinky->mIt = 0;
		mBlinky->mIsMoving = false;
		mBlinky->CurrentPositionOnGrid = 321;
		mPinky->pathToPacMan = (mGameMap->BFS(375, mPinky->mPacManTile));
		mPinky->mIt = 0;
		mPinky->mIsMoving = false;
		mPinky->CurrentPositionOnGrid = 375;

		mPacMan->mIsMoving = false;
		mPacMan->CurrentPositionOnGrid = 657;
		mPacMan->mPacMan->PositionTextureArea(mGameMap->mGrid->mTiles[657].mTile.x, mGameMap->mGrid->mTiles[657].mTile.y - 8);

		mUI->mIsRevealPlayerOne = true;
		mUI->mIsRevealReady = true;

		if (mUI->mIsRevealPlayerOne && deltaTime >= 1.0) {

			mUI->mIsRevealPlayerOne = false;
			mIsHit = false;
		}
		if (deltaTime >= 3.0) {

			mUI->mIsRevealReady = false;
			
			mIsReady = false;
			mIsPlaying = true;
			//make reset function later
			mPacMan->mCollider.x = mPacMan->mPacMan->mTextureArea.x + (mPacMan->mPacMan->mTextureArea.w - mPacMan->mCollider.w) / 2;
			mPacMan->mCollider.y = mPacMan->mPacMan->mTextureArea.y + (mPacMan->mPacMan->mTextureArea.h - mPacMan->mCollider.h) / 2;
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