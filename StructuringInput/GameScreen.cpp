#include "GameScreen.h"

GameScreen::GameScreen() {

	mGameMap = new GameMap;
	mPacMan = new PacManPlayer(mGameMap->square, mGameMap);
	mBlinky = new Ghost(mGameMap->square, mGameMap, "Blinky", mPacMan);
	mPinky = new Ghost(mGameMap->square, mGameMap, "Pinky", mPacMan);
	mInput = InputManager::Instance();

	mAllGhosts.push_back(mBlinky);
	mAllGhosts.push_back(mPinky);

	StageEntities();

	mIsHit = false;
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
}

void GameScreen::StageEntities() {

	//scaling and positioning pacman
	int pacXOffset = 0, pacYOffset = 3;
	//mPacMan->mPacMan->PositionTextureArea(mGameMap->mGrid->mTiles[29].mTile.x, mGameMap->mGrid->mTiles[29].mTile.y);
	//mPacMan->mPacMan->ScaleTextureArea(2, 0, 0);

	mBlinky->mGhost->PositionTextureArea(mGameMap->mGrid->mTiles[99].mTile.x - pacXOffset, mGameMap->mGrid->mTiles[99].mTile.y - pacYOffset);
	mBlinky->mGhost->ScaleTextureArea(2, 0, 0);

	mPinky->mGhost->PositionTextureArea(mGameMap->mGrid->mTiles[420].mTile.x - pacXOffset, mGameMap->mGrid->mTiles[420].mTile.y - pacYOffset);
	mPinky->mGhost->ScaleTextureArea(2, 0, 0);

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

	//MovementController();

	if (!mIsHit) {
		mPacMan->Update();
		mBlinky->Update();
		mBlinky->mPacManTile = mPacMan->CurrentPositionOnGrid;
		mPinky->Update();
		mPinky->mPacManTile = mPacMan->CurrentPositionOnGrid;
		mGameMap->Update();

		CollisionHandler();
	}
	
}

void GameScreen::Render() {

	mGameMap->Render();
	mPacMan->Render();
	mPinky->Render();
	mBlinky->Render();
}