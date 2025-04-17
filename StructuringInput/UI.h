#ifndef UI_H
#define UI_H
#include "Texture.h"
#include "GameMap.h"

using namespace SDLCore;
class UI {

public:
	UI(GameMap* gameMap);
	~UI();

	void Update();
	void Render();

	Texture* m1Up;
	Texture* mHighScore;
	Texture* mScore;
	Texture* mHighScoreNumber;
	Texture* mPlayerOne;
	Texture* mReady;
	Texture* mRound;
	Texture* mGameOver;
	Texture* mPacMan;
	Texture* mPacMan2;
	Texture* mPacMan3;

	bool mIsRevealPlayerOne;
	bool mIsRevealReady;
	bool mIsRevealGameOver;

	bool mIsRevealPac1;
	bool mIsRevealPac2;
	bool mIsRevealPac3;

	SDL_Color mFontColor;

private:
	void ResetTimer();
	int startTicks;
	int elapsedTicks;
	float deltaTime;
	bool mIsRevealed;

};

#endif