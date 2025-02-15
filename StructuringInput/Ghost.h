#ifndef Ghost_H
#define Ghost_H
#include "Texture.h"
#include "InputManager.h"
#include "GameMap.h"
#include "PacManPlayer.h"

using namespace SDLCore;

class Ghost {

public:

	Ghost(SDL_Rect moveSquare, GameMap* gameMap, std::string name, PacManPlayer* pacMan);
	~Ghost();

	SDL_Rect mMoveSquare;
	GameMap* mGameMap;
	PacManPlayer* mPacMan;

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
	std::string mGhostName;

	int CurrentPositionOnGrid;

	SDL_Rect mCollider;

	void GameOver();

private:

	//Graphics* mGraphics;
	InputManager* mInput;
	Animator* mAnimator;

	float mMoveSpeed;

	int startTicks;
	int elapsedTicks;
	float deltaTime;
};

#endif // !PacManPlayer