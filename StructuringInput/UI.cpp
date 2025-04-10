#include "UI.h"

UI::UI(GameMap* gameMap) {

	mFontColor.r = 255;
	mFontColor.g = 255;
	mFontColor.b = 255;
	mFontColor.a = 255;

	std::string text = "1UP";
	m1Up = new Texture("Emulogic.ttf", text, 20, mFontColor, (Graphics::Instance()->SCREEN_WIDTH / 3) - (text.size() / 2) * 20, 0);
	text = "High Score";
	mHighScore = new Texture("Emulogic.ttf", text, 20, mFontColor, (Graphics::Instance()->SCREEN_WIDTH / 2) - (text.size() / 2) * 20, 0);
	text = "0000000";
	mScore = new Texture("Emulogic.ttf", text, 20, mFontColor, (Graphics::Instance()->SCREEN_WIDTH / 3) - (text.size() / 2) * 20, 20);
	text = "0000000";
	mHighScoreNumber = new Texture("Emulogic.ttf", text, 20, mFontColor, (Graphics::Instance()->SCREEN_WIDTH / 2) - (text.size() / 2) * 20, 20);
	text = "Round 1";
	mRound = new Texture("Emulogic.ttf", text, 20, mFontColor, (Graphics::Instance()->SCREEN_WIDTH / 2) - (text.size() / 2) * 20, 
																	gameMap->mMapTexture->mTextureArea.y + gameMap->mMapTexture->mTextureArea.h);

	text = "Player One";
	mFontColor.r = 0;
	mFontColor.g = 255;
	mFontColor.b = 255;
	mFontColor.a = 255;
	mPlayerOne = new Texture("Emulogic.ttf", text, 20, mFontColor, gameMap->mGrid->mTiles[317].mTile.x - 5, gameMap->mGrid->mTiles[317].mTile.y);

	text = "Ready!";
	mFontColor.r = 255;
	mFontColor.g = 255;
	mFontColor.b = 0;
	mFontColor.a = 255;
	mReady = new Texture("Emulogic.ttf", text, 20, mFontColor, gameMap->mGrid->mTiles[487].mTile.x, gameMap->mGrid->mTiles[487].mTile.y - 5);

	//reset back to white
	mFontColor.r = 255;
	mFontColor.g = 255;
	mFontColor.b = 255;
	mFontColor.a = 255;

	startTicks = SDL_GetTicks();
	elapsedTicks = 0;
	deltaTime = 0.0f;

	mIsRevealed = true;
	mIsRevealPlayerOne = false;
	mIsRevealReady = false;
}

UI::~UI() {


}

void UI::ResetTimer() {

	startTicks = SDL_GetTicks();
	elapsedTicks = 0;
	deltaTime = 0.0f;
}

void UI::Update() {

	elapsedTicks = SDL_GetTicks() - startTicks;
	deltaTime = elapsedTicks * 0.001f;

	if (deltaTime >= 0.25f) {

		mIsRevealed = !mIsRevealed;
		ResetTimer();
	}
}

void UI::Render() {

	mHighScore->Render();

	if(mIsRevealed)
		m1Up->Render();

	mScore->Render();
	mHighScoreNumber->Render();

	if(mIsRevealPlayerOne)
		mPlayerOne->Render();
	if(mIsRevealReady)
		mReady->Render();

	mRound->Render();
}