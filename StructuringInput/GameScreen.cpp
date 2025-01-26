#include "GameScreen.h"

GameScreen::GameScreen() {

	mGameMap = new GameMap;
	mPacMan = new PacManPlayer(mGameMap->square, mGameMap);
	mGhost = new Ghost(mGameMap->square, mGameMap);
	mInput = InputManager::Instance();

	StageEntities();
}

GameScreen::~GameScreen() {

	delete mGameMap;
	mGameMap = NULL;

	delete mPacMan;
	mPacMan = NULL;

	delete mGhost;
	mGhost = NULL;

	mInput = NULL;
}

void GameScreen::StageEntities() {

	//scaling and positioning pacman
	int pacXOffset = 0, pacYOffset = 3;
	mPacMan->mPacMan->PositionTextureArea(mGameMap->mGrid->mTiles[29].mTile.x, mGameMap->mGrid->mTiles[29].mTile.y - pacYOffset);
	mPacMan->mPacMan->ScaleTextureArea(2, 0, 0);

	mGhost->mGhost->PositionTextureArea(mGameMap->mGrid->mTiles[99].mTile.x - pacXOffset, mGameMap->mGrid->mTiles[99].mTile.y - pacYOffset);
	mGhost->mGhost->ScaleTextureArea(2, 0, 0);

	//can pacnan move to this square?
}

void GameScreen::MovementController() {

}

void GameScreen::Update() {

	//MovementController();
	mPacMan->Update();
	mGhost->Update();
	mGhost->mPacManTile = mPacMan->CurrentPositionOnGrid;
	mGameMap->Update();
}

void GameScreen::Render() {

	mGameMap->Render();
	mPacMan->Render();
	mGhost->Render();
}