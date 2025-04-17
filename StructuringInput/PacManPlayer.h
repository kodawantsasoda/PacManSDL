#ifndef PacManPlayer_H
#define PacManPlayer_H
#include "Texture.h"
#include "InputManager.h"
#include "GameMap.h"
#include "Animator.h"
#include "Collider.h"
#include "Timer.h"

using namespace SDLCore;

class PacManPlayer {

public:
	enum PACMAN_DIRECTION { up, right, down, left};

public:
	//constructors & functions
	PacManPlayer(SDL_Rect moveSquare, GameMap* gameMap);
	~PacManPlayer();

	void Move(char input);

	//currently doesnt really work the way I want it...
	int GetTileInFrontOfMouth();

	void Reset();

	//functions initiate pac-man's dying animation and game over state
	bool GameOver();
	void SetDeathFrame();

	void Update();
	void Render();


public:
	//members
	//reference to the currently created gameMap
	GameMap* mGameMap;
	Texture* mPacMan;

	SDL_Rect mCollider;
	Collider mColliderEntity;

	//members for moving, and identfying direction 
	SDL_Rect mMoveSquare;
	bool mIsMoving;
	char mCurrentInput;
	int mTargetTileX;
	int mTargetTileY;

	const int XPOSDEATHCLIP = 487;
	const int OFFSETTEXTURE = 8;

	PACMAN_DIRECTION mDirection;
	
	//change to mCurrentPositionOnGrid
	int mCurrentPositionOnGrid;

	bool mIsPoweredUp;

	//player score
	std::vector<int> mScore;

private:
	//references
	InputManager* mInput;
	Animator* mAnimator;
	Animator* mAnimatorLeft;
	Animator* mDeathAnimator;
	Timer mTimer;
	Timer mPowerUpTimer;

	float mMoveSpeed;
};

#endif // !PacManPlayer
