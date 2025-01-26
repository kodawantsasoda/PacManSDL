#ifndef Ghost_H
#define Ghost_H
#include "Texture.h"
#include "InputManager.h"
#include "GameMap.h"

using namespace SDLCore;

class Ghost {

public:

	Ghost(SDL_Rect moveSquare, GameMap* gameMap);
	~Ghost();

	SDL_Rect mMoveSquare;
	GameMap* mGameMap;

	void Update();
	void Render();

	void Move();
	std::vector<int> pathToPacMan;
	int mNextTile;
	int mIt;
	int mPacManTile;
	bool mIsMoving;
	int mTargetTileX;
	int mTargetTileY;
	Texture* mGhost;

	int CurrentPositionOnGrid;

private:

	//Graphics* mGraphics;
	InputManager* mInput;

	float mMoveSpeed;

	int startTicks;
	int elapsedTicks;
	float deltaTime;
};

#endif // !PacManPlayer