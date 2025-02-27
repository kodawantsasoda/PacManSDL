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

	bool mIsRevealPlayerOne;
	bool mIsRevealReady;

private:
	void ResetTimer();
	int startTicks;
	int elapsedTicks;
	float deltaTime;
	bool mIsRevealed;

};

#endif