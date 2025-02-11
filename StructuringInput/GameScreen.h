#ifndef GameScreen_H
#define GameScreen_H
#include "PacManPlayer.h"
#include "Ghost.h"
#include "GameMap.h"
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

	void StageEntities();
	void CollisionHandler();

private:

	PacManPlayer* mPacMan;
	Ghost* mBlinky;
	Ghost* mPinky;
	GameMap* mGameMap;
	InputManager* mInput;

	std::vector<Ghost*> mAllGhosts;
	
	bool mIsHit;
};

#endif

