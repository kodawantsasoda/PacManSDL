#ifndef Ghost_H
#define Ghost_H
#include "Texture.h"
#include "InputManager.h"
#include "GameMap.h"
#include "PacManPlayer.h"
#include "Timer.h"

using namespace SDLCore;

class Ghost {

public:

	Ghost(SDL_Rect moveSquare, GameMap* gameMap, std::string name, PacManPlayer* pacMan);
	~Ghost();

	void GameOver();
	void Move();

	void Update();
	void Render();

public:

	Texture* mGhost;
	std::string mGhostName;
	SDL_Rect mCollider;

	SDL_Rect mMoveSquare;
	GameMap* mGameMap;
	PacManPlayer* mPacMan;

	//Members for Ghost path to pacman
	std::vector<int> pathToPacMan;
	int mNextTile;
	int mIt;
	int mPacManTile;
	bool mIsMoving;
	int mTargetTileX;
	int mTargetTileY;

	//change name to mCurrentPositionOnGrid
	int CurrentPositionOnGrid;

private:

	Timer mTimer;

	//Graphics* mGraphics;
	InputManager* mInput;
	Animator* mAnimator;

	float mMoveSpeed;
};

#endif