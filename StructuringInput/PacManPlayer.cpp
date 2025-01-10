#include "PacManPlayer.h"

PacManPlayer::PacManPlayer(SDL_Rect moveSquare, GameMap* gameMap) {

	mInput = InputManager::Instance();

	mPacMan = new Texture("PMSpriteSheet.png");
	mPacMan->ClipLocalTexture(472, 0, 13, 15);

	mMoveSquare = moveSquare;
	mGameMap = gameMap;

	CurrentPositionOnGrid = 29;
	mScore.push_back(CurrentPositionOnGrid);
}

PacManPlayer::~PacManPlayer() {

	mInput = NULL;

	delete mPacMan;
	mPacMan = NULL;

	mGameMap = NULL;
}

void PacManPlayer::MoveUp() {

	int x = mPacMan->mTextureArea.x, y = mPacMan->mTextureArea.y - mMoveSquare.h;
	mPacMan->PositionTextureArea(x, y);
	CurrentPositionOnGrid -= mGameMap->mGrid->GetColumns();
	
	mScore.push_back(CurrentPositionOnGrid);
	Graphics::Instance()->FillRectInGrid(mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile, 0, 0, 0, 0);
	printf("%d\n", CurrentPositionOnGrid);
}
void PacManPlayer::MoveDown() {

	int x = mPacMan->mTextureArea.x, y = mPacMan->mTextureArea.y + mMoveSquare.h;
	mPacMan->PositionTextureArea(x, y);
	CurrentPositionOnGrid += mGameMap->mGrid->GetColumns();

	mScore.push_back(CurrentPositionOnGrid);
	Graphics::Instance()->FillRectInGrid(mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile, 0, 0, 0, 0);
	printf("%d\n", CurrentPositionOnGrid);
}
void PacManPlayer::MoveRight() {

	int x = mPacMan->mTextureArea.x + mMoveSquare.w, y = mPacMan->mTextureArea.y;
	mPacMan->PositionTextureArea(x, y);
	CurrentPositionOnGrid++;

	mScore.push_back(CurrentPositionOnGrid);
	Graphics::Instance()->FillRectInGrid(mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile, 0, 0, 0, 0);
	printf("%d\n", CurrentPositionOnGrid);

}
void PacManPlayer::MoveLeft() {

	int x = mPacMan->mTextureArea.x - mMoveSquare.w, y = mPacMan->mTextureArea.y;
	mPacMan->PositionTextureArea(x, y);
	CurrentPositionOnGrid--;

	mScore.push_back(CurrentPositionOnGrid);
	Graphics::Instance()->FillRectInGrid(mGameMap->mGrid->mTiles[CurrentPositionOnGrid].mTile, 0, 0, 0, 255);
	printf("%d\n", CurrentPositionOnGrid);
}

void PacManPlayer::Update() {

	if (mInput->IsKeyPressed(SDL_SCANCODE_W)) {

		if (mGameMap->mGrid->mTiles[CurrentPositionOnGrid - mGameMap->mGrid->GetColumns()].mIsWall)
			printf("WALLMOFO");
		else
			MoveUp();
	}
	if (mInput->IsKeyPressed(SDL_SCANCODE_A)) {
		if (mGameMap->mGrid->mTiles[CurrentPositionOnGrid - 1].mIsWall)
			printf("WALLMOFO");
		else
			MoveLeft();
	}
	if (mInput->IsKeyPressed(SDL_SCANCODE_S)) {
		if (mGameMap->mGrid->mTiles[CurrentPositionOnGrid + mGameMap->mGrid->GetColumns()].mIsWall)
			printf("WALLMOFO");
		else
			MoveDown();
	}
	if (mInput->IsKeyPressed(SDL_SCANCODE_D)) {
		if (mGameMap->mGrid->mTiles[CurrentPositionOnGrid + 1].mIsWall)
			printf("WALLMOFO");
		else
			MoveRight();
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