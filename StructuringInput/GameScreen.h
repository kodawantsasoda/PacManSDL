#ifndef GameScreen_H
#define GameScreen_H
#include "PacManPlayer.h"
#include "GameMap.h"

using namespace SDLCore;

//controls everything thats on the game screen during main gameplay

class GameScreen {

public:

	GameScreen();
	~GameScreen();

	void Update();
	void Render();

	void StageEntities();
	void MovementController();

private:

	PacManPlayer* mPacMan;
	GameMap* mGameMap;
	InputManager* mInput;

};

#endif

