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

	void SpriteClipGhosts();
	void GameOver();
	void Reset();
	void Move();
	void Wave();
	void HandleEatState();
	void ReturnHome();

	void Update();
	void Render();

public:

	Texture* mGhost;
	std::string mGhostName;
	SDL_Rect mCollider;
	Collider mColliderEntity;

	SDL_Rect mMoveSquare;
	GameMap* mGameMap;
	PacManPlayer* mPacMan;

	Timer mEatableTimer;
	bool mIsEatable;

	//ghost ai tile patterns
	const std::vector<int> BLINKYPATTERN{49, 250, 43};
	const std::vector<int> PINKYPATTERN{586, 749, 575};
	const std::vector<int> INKYPATTERN{566, 731, 740};
	const std::vector<int> CLYDEPATTERN{230, 29, 40};
	int mPatternIterator;

	//Members for Ghost path to pacman
	std::vector<int> pathToPacMan;
	int mNextTile;
	int mIt;
	int mPacManTile;
	bool mIsMoving;
	int mTargetTileX;
	int mTargetTileY;

	int mCurrentPositionOnGrid;

	bool mIsDead;
	bool mIsChanging;
	bool mReturnedHome;

	Animator* mAnimator;

private:

	Timer mTimer;
	Timer mWaveTimer;

	//Graphics* mGraphics;
	InputManager* mInput;
	

	float mMoveSpeed;
	float mNormalSpeed;
	float mChaseSpeed;
	float mDeadSpeed;

	bool mIsEndWave;
};

#endif