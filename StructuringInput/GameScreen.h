#ifndef GameScreen_H
#define GameScreen_H
#include "PacManPlayer.h"
#include "Ghost.h"
#include "GameMap.h"
#include "UI.h"
#include "Collider.h"	
#include <vector>

using namespace SDLCore;

//controls everything thats on the game screen during main gameplay

class GameScreen {

public:

	GameScreen();
	~GameScreen();

	void Update();
	void Render();

	//void StageEntities();
	void CollisionHandler();

private:

	PacManPlayer* mPacMan;
	Ghost* mBlinky;
	Ghost* mPinky;
	Ghost* mInky;
	Ghost* mClyde;
	GameMap* mGameMap;
	UI* mUI;
	InputManager* mInput;
	Timer mTimer;

	std::vector<Ghost*> mAllGhosts;
	
	bool mIsHit;
	bool mHasAte;
	bool mIsDying;
	bool mIsReady;
	bool mIsPlaying;
	bool mIsNextLevel;
	bool mMapAnimation;

	int* mRoundScore;
	int mRoundNum;
};

#endif

