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
	//constructors & functions
	PacManPlayer(SDL_Rect moveSquare, GameMap* gameMap);
	~PacManPlayer();

	void Update();
	void Render();

	void Move(char input);

	//currently doesnt really work the way I want it...
	int GetTileInFrontOfMouth();

	//functions initiate pac-man's dying animation and game over state
	bool GameOver();
	void SetDeathFrame();


public:
	//members
	//reference to the currently created gameMap
	GameMap* mGameMap;

	Texture* mPacMan;
	SDL_Rect mCollider;

	//members for moving, and identfying direction 
	SDL_Rect mMoveSquare;
	bool mIsMoving;
	char mCurrentInput;
	int mTargetTileX;
	int mTargetTileY;

	const int XPOSDEATHCLIP = 487;
	
	//change to mCurrentPositionOnGrid
	int CurrentPositionOnGrid;

	//player score
	std::vector<int> mScore;

private:
	//references
	InputManager* mInput;
	Animator* mAnimator;
	Animator* mDeathAnimator;
	Timer mTimer;

	float mMoveSpeed;
};

#endif // !PacManPlayer
